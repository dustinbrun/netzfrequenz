# Bestimmung der Netzfrequenz mittels Arduino

Dies ist eine bearbeitete Version von https://github.com/ratopi/netzfrequenz

Neue Funtionen:
- Möglichkeit zum Aufzeichen von Daten auf eine SD Karte 
- Debug LED, sodass auch ohne Seriellen Monitor erkannt werden kann, ob die SD Karte korrekt erkannt wird (leuchtet dauerhaft bei Fehler)
- Minimum/Maximum Grenze, damit offensichtich falsche Werte nicht aufgezeichnet werden

Die SD Karten Steuerung wurde inspiriert von dem Artikel "Guide to SD Card Module with Arduino" gefunden auf der Seite randomnerdtutorials.com (https://randomnerdtutorials.com/guide-to-sd-card-module-with-arduino/).

--- Orginaltext ---

Dieser kleine Sketch zeigt wie man mittels einer einfachen kurzen Antenne
an einem Analog-Port des Arduinos die aktuelle Netzfrequenz des Stromnetzes
messen kann.

Die Messung der Netzfrequenz kann interessant sein um zu beobachten, ob momentan genug
oder zu wenig Strom ins Netz eingespeist wird.
Wird zu wenig Strom eingespeist, so sinkt die Netzfrequenz.
Wird zu viel Strom eingespeist, so steigt die Netzfrequenz.

Eine solche Messung könnte in Zukunft in Zusammenhang mit "Smart Grids" interessant werden, da sich über die Frequenzmessung an jedem Ort unabhängig von einer Zentrale der Lastzustand des Gesamtnetzes beurteilen lässt und somit Verbraucher gezielt vor Ort ein und ausgeschaltet werden könnten.
Siehe dazu auch: http://www.solarify.eu/2015/01/27/205-smart-grid-einfach-dezentral-selbstorganisiert/


## Programm

An Port A0 wird einfach ein kurzes Stück Draht (beispielsweise 10cm) angeschlossen.
Das andere Ende des Drahtes wird offen gelassen, so fungiert der Draht als Antenne und 
Port A0 "empfängt" dann ein verrauschtes Netzbrummen.

Im Programm wird der zeitliche Abstand der Minmumdurchgänge dieses Brummen gemessen, was
der Periodendauer entspricht.
Aus dem Kehrwert der Periodendauer ergibt sich dann die Frequenz.

Um die Sache etwas genauer zu machen wird die Zeit für 50 Perioden gemessen und dann
gemittelt.

Die gemessene Frequenz kann dann mit der Frequenz von http://www.netzfrequenzmessung.de/
verglichen werden.

Bei meinen Versuchen hat sich gezeigt, dass es eine Abweichung zwischen der von mir gemessenen
Frequenz und der "offiziellen" Netzfrequenz (von http://www.netzfrequenzmessung.de/) gibt.
Woran diese Abweichung liegt ist mir momentan noch nicht klar.

Ich kann mir momentan folgende Ursachen hierfür denken:
* Eine Abweichung des Quartz auf dem Arduino-Board
* Fehlende Interrupts fuer die Bestimmung der "micros()"; vielleicht durch die A/D-Wandlung

(Falls irgendjemand eine Idee, kann er mich gerne üeber GitHub kontaktieren. Danke.)


## Schaltungsaufbau

![Aufbau](netzfrequenz_Steckplatine.png)



Viel Spaß

ratopi
dustinbrun