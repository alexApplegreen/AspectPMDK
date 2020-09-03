# Arbeitspakete Bachelorarbeit Alexander Tepe

Da die Zeitspanne von Beginn der Arbeit bis zur Abgabe der Arbeit 3 Monate beträgt, liegt es nahe,
den Arbeitsablauf der Arbeit grob in 3 große Teilstücke zu gliedern:

* Monat 1: Planung / Gliederung
* Monat 2: Implementierung
* Monat 3: Integration / Evaluierung

Der Ablauf der schriftlichen Ausarbeitung soll sich ebenfalls an dieser Gliederung orientieren.
Neben der Bearbeitung der praktischen Arbeitspakete soll parallel immer das dazu passende Kapitel
in der schriftlichen Ausarbeitung geschrieben werden.
Auf diese Weise ist das Thema immer "frisch" genug um in allen nötigen Details niedergeschrieben
werden zu können.
Der allgemeine Ablauf soll agil sein, sodass in der dritten Phase nicht alle Tests fehlschlagen und
die Evaluierung wegen Troubleshooting zu kurz kommt. Um möglichst agil zu sein, will ich ein
Backlog führen, in dem Features der fertigen Software nach und nach ergänzt und getestet werden.
Die Implementierung der Unit Tests kann also schon in Phase 2 geschehen, während die
Integrationstests in Phase 3 geschehen.

## Planung und Gliederung (Monat 1)
Im ersten Monat sollen alle nötigen Designentscheidungen getroffen werden, die zu einer
funktionierenden Software führen sollen. Ausgangspunkt ist hierbei die Annahme, dass die
zu entwickelnde Software aus Code von Datenstrukturen, welche auf herkömmlichen Speicher ausgelegt
sind, so zu verändern, dass der Code auf persistentem Speicher funktioniert.
Und zwar mit möglichst geringen expliziten Eingriffen des Entwicklers am Ausgangscode.
Es muss also geklärt werden:

* Welche Teile des Ausgangscodes müssen modifiziert werden?
* Wo lassen sich Muster in der Modifizierung erkennen, die ausgenutzt werden können?
* Ansätze für Best Practices in der Umsetzung dieser Muster abwägen (evtl. Literatur hinzuziehen)
* An welchen Stellen soll die Software an den Code andocken?
* Wie genau soll die Modifikation des Codes funktionieren?

Des weiteren soll in dieser Phase das Backlog gefüllt werden und ich will mehr Literatur heranziehen
um Designentscheidungen so belastbar wie möglich vertreten zu können. Zu diesem Zweck ist
wahrscheinlich besonders die Literatur aus dem Bereich Aspekte und Transaktionen in Java hilfreich.
Außerdem kann während dieser Phase schon grob geklärt werden, wie die konkreten Messungen zur Gegenüberstellung
mit der C++ API ablaufen können.

### Kapitel der Ausarbeitung Monat 1:
* Technische Einführung in Persistenten Speicher ("Was ist das?")
* Motivation für die Entwicklung einer Abstraktionsschicht für das PMDK
* Dokumentation der geplanten Software (UML, vlt. Doxygen, etc.), Erklärung dieser.

### Ziel von Monat 1:
* 3 Kapitel der Ausarbeitung
* Gefülltes Backlog
* Sinnvolle Planung der Softwarearchitektur

## Implementierung (Monat 2)
Reine Implementierung anhand des Backlogs aus dem Vormonat.
Für jeden Eintrag aus dem Backlog soll die Software um eine Funktion erweitert werden. Außerdem sollen
Unit Tests dafür geschrieben und durchgeführt werden.
Ich rechne damit, dass ich in dieser Phase ab und zu vom geplanten weg abweichen muss. Die Entscheidungen,
welche zu dazu führten sollen dann dokumentiert und erklärt werden.

### Kapitel der Ausarbeitung Monat 2:
* noch fraglich, ob überhaupt Falls ja: Rechtfertigungen für Abweichungen vom Plan

### Ziel von Monat 2:
* 1 Kapitel der Ausarbeitung
* Funktionierende Software Units.

## Integration / Evaluierung (Monat 3)
Zuletzt soll die Software auf der realen Hardware getestet werden. Für diesen Zweck müssen wahrscheinlich eigene
Tests abseits der Unit Tests geschrieben werden.
Außerdem soll in dieser Phase eine Gegenüberstellung zwischen meiner Software und der C++ API des PMDK
passieren. Planungen aus Monat 1 müssen hier sicherlich verfeinert oder überarbeitet werden.

### Kapitel der Ausarbeitung Monat 3:
* Erklärung von Tests und Messungen auf der realen Hardware
* Evaluierung der Ergebnisse & Gegenüberstellung mit C++ API
* Fazit (Was hat man rückblickend gelernt? Waren alle Entscheidungen klug?)
* Ausblick (Was wäre in Zukunft besser machbar?)

### Ziel von Monat 3:
* Funktionierende Integration auf realer Hardware
* Erkenntnisse durch Messungen, sodass es etwas gegenüberzustellen gibt
* 4 Kapitel der Ausarbeitung
