import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

classes = ['AOPQueue', 'PQueue']
aop_data = [52913,5729,2765,2468,2643,2462,2520,2327,2484,2216,3000,2378,2377,2320,2528,2755,2500,2328,2497,2325,2508,2138,2080,2083,2481,2066,2111,2481,2084,2514,2122,2159,2506,2502,2063,2123,2536,2148,2495,2131,2142,2088,3012,2302,2930,2306,2919,2314,2416,2279,2925,2298,2125,2474,2140,2495,2139,2496,2511,2072,2146,2463,2121,2090,2481,2105,2115,2472,2082,2536,2485,2081,2498,2082,2893,2320,2485,2269,2872,2344,2881,2281,2889,2718,2114,2115,2134,2475,2108,2547,2106,2459,2125,2509,2125,2102,2521,2158,2546,3466]
p_data = [51743,6967,2328,2406,2391,2409,2057,2585,2089,2604,2103,1889,2582,2217,2035,2574,1936,2609,2034,2595,2042,2195,1844,2239,1859,2190,1845,2189,1855,2191,1823,2220,2216,1845,2191,1743,2203,1842,2187,1818,2245,2194,1840,2710,2049,2605,2385,2564,2035,2248,2454,2609,2463,1751,2205,1859,2224,2195,1746,2185,1860,2168,1845,1929,2179,2181,2191,1824,2189,1842,1854,1834,1836,2213,2222,1888,2579,2241,2394,2586,2040,2564,2385,2141,2366,2190,1826,2194,1743,2189,1895,2183,1854,2175,2222,2193,2199,2200,2198,3743]
data = {'AOPQueue' : aop_data, 'PQueue' : p_data}
df = pd.DataFrame(data=data)

sns.set_theme()
ax = sns.boxplot(data=df, showfliers=False)
ax.set(ylabel = 'Zeit in Nanosekunden')

plt.show()
