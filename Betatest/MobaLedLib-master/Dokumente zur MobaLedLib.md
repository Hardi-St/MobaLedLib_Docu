# Dokumente zur MobaLedLib

Seit Anfang M�rz 2020 gibt es ein eigenes Wiki f�r die MobaLedLib. Hier findet man alle ben�tigten Informationen:
[MobaLedLib Wiki](https://wiki.mobaledlib.de/doku.php)

Darum werden die folgenden Links nicht weiter gepflegt�


Dieses Dokument enth�lt Links zu allen wichtigen Dokumenten der MobaLedLib. Mit einem Klick auf die unterstrichenen �berschriften kommt man direkt zu dem entsprechenden Dokument. Dort kann man es lesen oder herunter laden.

Das Hauptverzeichnis aller Dokumente erreicht man �ber diesen Link: [MobaLedLib_Docu](https://github.com/Hardi-St/MobaLedLib_Docu)

Meldet euch bitte bei fehlerhaften Links, wenn Ihr Verbesserungsvorschl�ge habt, wenn Ihr an der Dokumentation mitarbeiten wollt, wenn es Probleme gibt, �.

bei:  [MobaLedLib@gmx.de](mailto:MobaLedLib@gmx.de)

# Software Dokumentation

[MobaLedLib: Ein kurzer �berblick](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/MobaLedLib%20Ein%20kurzer%20Ueberblick.pdf)

Dieses Dokument gibt einen kurzen �berblick der Arduino Bibliothek. Es beschreibt die einzelnen Funktionen der Bibliothek im Detail.

[MobaLedLib Short Overview](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/MobaLedLib%20Short%20Overview.pdf)

This is the English version of the Documentation. Unfortunately it�s not always updated when to the changes in the German version. You are welcome to help to keep the document up-to-date.

[MobaLedLib Adresszuordnung und Rocrail Aktionen Ausgang](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Bedienungsanleitungen/MobaLedLib_Adresszuordnung_und_Rocrail_Aktionen_Ausgang.pdf)

Hier wird beschrieben wie man Aktionen der MobaLedLib mit RocRail steuert.

# Best�ckungsanleitungen

F�r die MobaLedLib existieren einige Platinen. Hier wird beschrieben wie die Platinen best�ckt werden und welche Best�ckungsvarianten es gibt. Au�erdem findet man hier Bauteillisten und Bezugsquellen.

[100-DE Arduino f�r LEDs Master Best�ckungsanleitung](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Bestueckungsanleitungen/100-DE_Arduino_fuer_LEDs_Master_Bestueckungsanleitung_20190721_V01-00_komprimiert.pdf)

Best�ckungsanleitung der Hauptplatine. Sie steuert alle LEDs und stellt die Verbindung zu DCC, Selectrix oder dem CAN Bus her.

[200-DE Verteilerplatine Universal Best�ckungsanleitung](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Bestueckungsanleitungen/200-DE_Verteilerplatine_Universal_LoetJumper_Bestueckungsanleitung.pdf)

Die H�user, Stra�enlaternen, Sound und Servo Module und alle anderen von der MobaLedLib angesteuerten Objekte werden einfach �ber Verteilerplatinen �hnlich einer Vielfachsteckdose angeschlossen. In diesem Dokument wird der Aufbau dieser Platine beschreiben.

[500-DE_Sound-Module_JQ6500_Bestueckungsanleitung](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Bestueckungsanleitungen/500-DE_Sound-Module_JQ6500_Bestueckungsanleitung.pdf)

Best�ckungsanleitung des JQ6500 Sound Moduls welches 5 verschiedene Ger�usche im direkten Zugriff abspielen kann und zus�tzlich zwei Ausg�nge f�r LEDs hat.

# Hardware Dokumentation

In diesem Abschnitt findet man die Schaltpl�ne, Layouts und Fertigungsunterlagen der Platinen.

[Arduino f�r LEDs Mainboard](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/Arduino_fuer_LEDs_Mainboard.zip)

Hauptplatine der MobaLedLib. Sie steuert alle LEDs und stellt die Verbindung zu DCC, Selectrix oder dem CAN Bus her.

[RGB_LED_Verteiler](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/RGB_LED_Verteiler.zip)

Hier sind die Daten der Verteilerplatine als Zip Datei verf�gbar.

[Sound_JQ6500](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/Sound_JQ6500.zip)

Sound Modul basierend auf dem JQ6500 Modul. Damit k�nnen bis zu 5 Sounds gezielt abgerufen werden. Beliebige weitere Sounds k�nnen sequenziell abgespielt werden. Die Sounds sind in einem internen Speicher abgelegt.

[MP3-TF-16F Sound Modul und WS2811](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/MP3-TF-16F%20Sound%20Modul%20und%20WS2811.pdf)

Einfacher Schaltplan mit dem MP3-TF-16F Sound Modul und einem WS2811 Chip. Damit k�nnen 14 Sounds gezielt abgerufen werden. Beliebige weitere Sounds k�nnen sequenziell abgespielt werden Sounds. Die Sounds werden auf einer Micro SD Karte gespeichert.

[S3PO Modul WS2811](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/S3PO_Modul_WS2811.zip)

Universal Modul welches Sound, Servos, Signale und Power Outputs enth�lt.

[Servo_LED](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/Servo_LED.zip)

Diese winzige Platine kann 3 Servos, ein Multiplex Signal oder Schrittmotoren ansteuern. Sie wird genauso wie die RGB Leds angesprochen und wird ist nur �ber eine 4-polige Leitung mit der Verteilerplatine verbunden.

[Tiny_UniProg](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/Tiny_UniProg.zip)

Auf der Servo LED Platine wird der kleine, 8-polige Arduino Bruder ATTiny85 verwendet. Zur Programmierung dieses Prozessors ben�tigt man diese Schaltung. Die Servo Module m�ssen �eigentlich� nur einmal Programmiert werden solange es keine Verbesserungen der Software gibt.

[PushButtonAction_4017](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Platinen/PushButtonAction_4017.zip)

Mit dieser Schaltung k�nnen bis zu 80 Schalter eingelesen werden. Das kann noch erweitert werden indem die Platinen kaskadiert werden. Sie kann au�erdem zum einlesen von �Knopfdruck Aktionen� an Anlagenrand eingesetzt werden. Dazu enth�lt sie WS2811 Chips mit denen die LEDs in den Tastern angesteuert werden. Das tolle daran ist, dass fast beliebig viele Taster �ber eine 8-polige Leitung mit dem Arduino verbunden werden k�nnen.

# Anwendungsbeispiele

[Stra�enlaternen](https://github.com/Hardi-St/MobaLedLib_Docu/blob/master/Anwendungsbeispiele/Strassenlaternen.pdf)

Hier beschreibt Armin den Anschluss von Stra�enlaternen �ber WS2811 und was man dabei beachten muss. Er zeigt auch anhand von Bildern wie das aussehen kann.

> Written with [StackEdit](https://stackedit.io/).

