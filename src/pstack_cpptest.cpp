#define CATCH_CONFIG_MAIN
#define POOL "./mempooltestdroelf"
#define POOL_TEST "./mempooltestinternal"

#include "util/log.h"
#include "pstack_cpp.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>
#include <stdexcept>
#include "util/catch.hpp"

pmem::obj::pool<PStack> pop;

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& testRunInfo) override {
        try {
            pop = pmem::obj::pool<PStack>::create(POOL, "", PMEMOBJ_MIN_POOL);
        }
        catch (pmem::pool_error e) {
            pop = pmem::obj::pool<PStack>::open(POOL, "");
        }

        pmem::obj::persistent_ptr<PStack> stack_ptr = pop.root();
        PStack* stack = stack_ptr.get();
        stack = new PStack(10);

        pop.persist(stack_ptr);
    }

    void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        while(!pop.root().get()->isEmpty()) {
            pop.root().get()->pop();
        }
        pop.persist(pop.root());
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        // prep persistent Stack for subsequent test of persistent properties
        pop.root().get()->push('O');
        pop.root().get()->push('L');
        pop.root().get()->push('L');
        pop.root().get()->push('A');
        pop.root().get()->push('H');

        pop.persist(pop.root());
        pop.close();
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("is empty initially", "[Stack]") {
    REQUIRE(pop.root().get()->isEmpty());
}

TEST_CASE("Can push / pop", "[Stack]") {
    pop.root().get()->push('A');
    REQUIRE_FALSE(pop.root().get()->isEmpty());

    char elem = pop.root().get()->pop();
    REQUIRE(elem == 'A');
}

// TODO test is failing
TEST_CASE("FIFO Works", "[Stack]") {
    pop.root().get()->push('O');
    pop.root().get()->push('L');
    pop.root().get()->push('L');
    pop.root().get()->push('A');
    pop.root().get()->push('H');

    char hallo[6];
    while(!pop.root().get()->isEmpty()) {
        int i = 0;
        hallo[i] = pop.root().get()->pop();
        i++;
    }
    hallo[5] = '\0';

    REQUIRE(strcmp(hallo, "HALLO") == 0);
}

// TODO Tests are failing
TEST_CASE("Constructor Tests", "[Stack]") {

    SECTION("Constructor throws Exception") {
        REQUIRE_THROWS_AS([&]() {
            PStack* stack = new PStack(2048);
        }(), std::invalid_argument);
    }

    SECTION("Constructor delegation works") {
        pmem::obj::pool<PStack> pop_section;
        try {
            pop_section = pmem::obj::pool<PStack>::create(POOL_TEST, "", PMEMOBJ_MIN_POOL);
        }
        catch (pmem::pool_error e) {
            pop_section = pmem::obj::pool<PStack>::open(POOL_TEST, "");
        }

        pmem::obj::persistent_ptr<PStack> stack_ptr_section = pop.root();
        PStack* stack = stack_ptr_section.get();
        stack = new PStack();
        pop_section.persist(stack_ptr_section);

        REQUIRE_NOTHROW([&]() {
            for (int i = 0; i < STACK_MAXSIZE; i++) {
                pop_section.root().get()->push('X');
            }
        });
        delete pop_section.root().get();
        pop_section.close();
    }
}
