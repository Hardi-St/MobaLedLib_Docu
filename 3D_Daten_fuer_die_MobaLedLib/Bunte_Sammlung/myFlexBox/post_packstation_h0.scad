// =====================================================================
//  Österreichische Post "Post-Station"  -  Spur H0 (1:87)
//  Für Bambu Lab + AMS (4 Farben: gelb, weiß, schwarz, grau), 0,2-mm-Düse
//
//  AUFTEILUNG DES KORPUS (alles druckbar ohne Stützen)
//   FRONT      dünne Platte (Front oben, Ironing). Nur die vorderste Schicht
//              (skin_t_m) ist mehrfarbig, der Rest grau. Hinten ein
//              zurückgesetzter Steckrand (lip_m = 1 mm).
//   RAHMEN     SOCKEL (schwarz, volle Tiefe, mit Magnettaschen und JST-Loch)
//              + 2 SEITENWÄNDE (grau). Wird aufrecht gedruckt (Sockel auf dem
//              Bett, Wände wachsen nach oben), als EIN Objekt mit 2 Teilen.
//   RÜCKSEITE  dünne Platte mit Steckrand (1 mm) und Lüftungsschlitzen.
//   Front und Rückseite werden mit dem Steckrand in den Rahmen gesteckt und
//   sitzen auf dem Sockel.
//
//  MAGNETE (2 x 8 mm Ø, 3 mm hoch)
//   Der Sockel ist im Maßstab nur 1,4 mm hoch. Die Magnete sitzen deshalb in
//   Taschen im Sockel (Boden mag_floor_m bleibt geschlossen, Quetschrippen
//   halten sie ohne Kleber) und ragen oben ca. 2,2 mm in den Innenraum. Front
//   und Rückseite haben dort runde Aussparungen. Die Positionen sind
//   absichtlich unsymmetrisch (7 mm links / 10 mm rechts vom Ende), das Modell
//   passt nur in EINER Ausrichtung auf Magnete mit gleichem Raster.
//   Polung: beide Magnete gleich einsetzen wie auf der Anlagenplatte.
//   BODENLOCH: ein Loch in der Mitte für einen 4-poligen JST-Stecker.
//
//  TEILE (Variable "part"), jeder STL = ein Filament
//    Front (zusammen als EIN Objekt mit mehreren Teilen in den Slicer laden!)
//      front_core   GRAU     Träger, Kopfleiste, Steckrand, Fugengrund
//      skin_yellow  GELB     Frontschicht Türen Spalten 1-4
//      skin_white   WEISS    Frontschicht Spalten 5-8 + Display-Fenster
//      skin_black   SCHWARZ  Post-Logo, Schrift, Terminal-Blende
//    Rahmen (zusammen als EIN Objekt laden)
//      frame_base   SCHWARZ  Sockel mit Magnettaschen + JST-Loch
//      frame_walls  GRAU     Seitenwände
//    Einzeln drucken
//      back         WEISS    Rückseite
//      canopy       GRAU     Deckel mit Überstand, 2 LED-Taschen, Kabelkanal
//      led_holder   SCHWARZ  Lichtkasten + Kabelschacht für die Display-LED
//    all            Vorschau aller Teile in Einbaulage
//
//  DECKEL-FÜHRUNG
//   Steckrahmen (Klemmnoppen) + 4 Führungsstifte; die Stifte greifen in
//   Löcher in der Oberkante von Front und Rückseite.
//
//  KABELWEGE
//   Deckel : 2 LEDs (1206), MITTIG zur Station (nicht zum Display) ->
//            je LED ein GERADER Kanal, rechtwinklig von der LED nach hinten
//            (spitzes 45-Grad-Dach, druckbar ohne Stützen) -> je LED ein
//            großer Auslass nach unten in die Station ->
//            durch den Hohlraum der Station -> Loch in der Sockelmitte -> Anlage.
//   Display: LED (1206) im Lichtkasten (led_holder) -> Kabelschacht nach
//            unten -> Loch in der Sockelmitte -> Anlage.
//  Hinweis: bei Vorschau-Problemen (F5) bitte mit F6 rendern.
// =====================================================================

/* [Ausgabe] */
part             = "all";    // all, front_core, skin_yellow, skin_white, skin_black, frame_base, frame_walls, back, canopy, led_holder
print_layout     = false;    // true = Druckausrichtung (für STL-Export)
scale_divisor    = 87;       // H0 = 1:87
right_side_white = true;     // Spalten 5-8 weiß (myflexbox-Optik), sonst gelb
show_back        = true;     // Rückseite in der Vorschau zeigen

/* [Druckparameter - Modellmaße in mm] */
skin_t_m      = 0.5;   // Dicke der farbigen Frontschicht = Logo-Einlegetiefe
wall_m        = 1.2;   // Wandstärke Rahmen (Seitenwände)
groove_m      = 0.30;  // Türfugen: Breite
groove_d_m    = 0.20;  //           Tiefe

/* [Teilung: Front / Rahmen / Rückseite - Modellmaße in mm] */
front_t_m     = 1.0;   // Front: Flansch (0,5 farbige Schicht + Träger)
back_t_m      = 1.0;   // Rückseite: Flansch
lip_m         = 1.0;   // zurückgesetzter Steckrand (Höhe) von Front und Rückseite
fit_m         = 0.08;  // Passungsspiel Steckrand <-> Rahmen

/* [Lüftungsschlitze Rückseite - angedeutet] */
vent_depth_m  = 0.5;   // Lüftungsschlitze nur eingraviert
vent_h_m      = 0.4;
vent_rows     = 6;
vent_pitch    = 90;    // Original-mm
vent_len      = 1000;  // Original-mm
vent_z        = [650, 1450];

/* [LEDs 1206 - Modellmaße in mm] */
led_w_m       = 3.6;   // Tasche für 1206 (Bauteil 3,2 x 1,6 x 1,1)
led_h_m       = 2.0;

/* [Deckel (Canopy)] */
canopy_front_m = 4.0;  // Überstand nach vorn
canopy_side_m  = 0.6;  // Überstand seitlich/hinten
canopy_led_dx  = 1000; // LEDs sitzen symmetrisch zur STATIONSMITTE: Mitte -/+ dx (Original-mm)
can_pocket_m   = 1.2;  // Tiefe der LED-Taschen
can_ch_w_m     = 1.6;  // Kabelkanal Breite (innen im Deckel, gerade, ohne Knick)
can_ch_z1_m    = 1.6;  // Kanal-Oberkante ab Deckel-Unterseite (darüber bleibt die Deckhaut)
can_ch_wall_m  = 0.3;  // senkrechter Teil der Kanalwand; darunter spitzes 45-Grad-Dach
can_open_w_m   = 6.0;  // Auslass nach unten (je LED einer, bewusst groß)
can_open_d_m   = 3.6;

/* [Magnete & Bodenloch - Modellmaße in mm] */
mag_d_m       = 8.0;   // Magnet Durchmesser
mag_h_m       = 3.0;   // Magnet Höhe
mag_clear_m   = 0.10;  // Spiel je Seite (Tasche = Magnet + 2 x Spiel)
mag_rib_m     = 0.15;  // Quetschrippen in der Tasche (3 Stück) - halten den Magnet ohne Kleber
mag_floor_m   = 0.6;   // Boden unter dem Magnet bleibt geschlossen (ca. 6 Schichten)
mag_left_m    = 7.0;   // Magnet 1: Mittelpunkt, Abstand zum LINKEN Ende
mag_right_m   = 10.0;  // Magnet 2: Mittelpunkt, Abstand zum RECHTEN Ende (absichtlich anders)
mag_notch_m   = 0.15;  // Aussparung in Front/Rückseite: Spiel je Seite um den Magnet
jst_w_m       = 12.8;  // Bodenloch für 4-poligen JST-Stecker (XH-4: ca. 12,4 x 5,8 + Spiel;
jst_h_m       = 6.2;   //   PH-4: ca. 10 x 4,5 -> Stecker nachmessen und hier anpassen)

/* [Steckverbindung Deckel <-> Station] */
plug_h_m      = 1.2;   // Höhe des Steckrahmens
plug_wall_m   = 0.6;   // Wandstärke des Steckrahmens
plug_clear_m  = 0.12;  // Spiel zur Kopfleiste
plug_bump_m   = 0.16;  // Klemmnoppen (gegen Spiel erhöhen -> strammer)
pin_d_m       = 0.8;   // Führungsstifte: Durchmesser
pin_len_m     = 1.1;   //                 Länge
pin_clear_m   = 0.08;  //                 Spiel je Seite im Loch
pin_x_m       = 2.4;   //                 Abstand der Achse vom seitlichen Rand
hole_depth_m  = 1.2;   //                 Lochtiefe in Front/Rückseite

/* [LED-Halter Display - Modellmaße in mm] */
holder_wall_m = 0.5;   // Wand Lichtkasten / Platte / Rückwand
duct_d_m      = 1.6;   // Tiefe Kabelschacht innen
holder_gap_m  = 0.2;   // Abstand zum Steckrand der Rückseite
holder_clr_m  = 0.1;   // Spiel in der Öffnung der Front

// ---------------------------------------------------------------
//  Original-Abmessungen (mm) - Post-Station Outdoor
//  Gesamt ca. 4,0 m x 0,80 m x 2,45 m (inkl. Deckel)
// ---------------------------------------------------------------
col_w    = 500;  term_w = 500;
n_left   = 4;    n_right = 3;
D        = 800;
H_plinth = 118;  H_door = 1980;  H_header = 143;
H_total  = 2450;

// Türhöhen je Spalte von unten nach oben (nach Foto, werden normiert)
left_cols_raw  = [ [78,78,78,78,78,78,78,158],
                   [78,78,78,78,78,78,78,158],
                   [78,78,39,39,39,39,39,39,39,39,39,39,158],
                   [157,39,39,39,39,39,39,39,39,39,39,158] ];
right_cols_raw = [ [78,78,39,39,39,39,39,39,39,39,39,39,158],
                   [78,78,78,78,78,78,78,158],
                   [78,78,78,78,78,78,78,158] ];
term_below_raw = [157,39,39,39];     // Terminalspalte: Türen unten
term_above_raw = [39,39,158];        // Türen oben
zone_raw       = 199;                // Terminal-Blende

// ---------------------------------------------------------------
//  Abgeleitete Werte (Original-mm)
// ---------------------------------------------------------------
S = 1 / scale_divisor;
function mm(v) = v / S;
function sum_to(v, n, i = 0) = (i >= n) ? 0 : v[i] + sum_to(v, n, i + 1);
function fit_to_door(v) = [for (x = v) x * H_door / sum_to(v, len(v))];

groove   = mm(groove_m);   groove_d = mm(groove_d_m);
skin_t   = mm(skin_t_m);   wall     = mm(wall_m);
tf  = mm(front_t_m); tb = mm(back_t_m);
lip = mm(lip_m);     fit = mm(fit_m);          clh = mm(holder_clr_m);
led_w = mm(led_w_m); led_h = mm(led_h_m);

left_cols  = [for (c = left_cols_raw)  fit_to_door(c)];
right_cols = [for (c = right_cols_raw) fit_to_door(c)];
xL      = n_left * col_w;
W       = n_left * col_w + term_w + n_right * col_w;
xc_t    = xL + term_w / 2;
z_body0 = H_plinth;
z_body1 = H_plinth + H_door;
z_head1 = z_body1 + H_header;
canopy_h = H_total - z_head1;
mag_pocket_d = mm(mag_d_m + 2 * mag_clear_m);   // Ø Tasche
mag_notch_d  = mm(mag_d_m + 2 * mag_notch_m);   // Ø Aussparung in Front/Rückseite
mag_top      = mm(mag_floor_m + mag_h_m);       // Oberkante Magnet (ab Sockel-Unterkante)
mag_x        = [mm(mag_left_m), W - mm(mag_right_m)];
col_bounds = concat([for (i = [1 : 1 : n_left]) i * col_w],
                    [for (i = [0 : 1 : n_right - 1]) xL + term_w + i * col_w]);

// Terminal-Zone
kn = H_door / (sum_to(term_below_raw, len(term_below_raw)) + zone_raw
               + sum_to(term_above_raw, len(term_above_raw)));
term_below = [for (x = term_below_raw) x * kn];
term_above = [for (x = term_above_raw) x * kn];
zone_h  = zone_raw * kn;
zone_lo = z_body0 + sum_to(term_below, len(term_below));
zone_hi = zone_lo + zone_h;
dsp = [xc_t, zone_hi - 111 * kn, 240, 220];     // Display-Fenster
scn = [xc_t, zone_hi - 172 * kn,  90,  90];     // Code-Scanner (Vertiefung)
scn_depth = 25;

// LED-Halter
h_wall  = mm(holder_wall_m);
h_duct  = mm(duct_d_m);
h_bw    = led_w + mm(0.6);                       // Schachtbreite innen
y_end   = D - tb - lip - mm(holder_gap_m);       // Rückkante Halter
y_pl    = y_end - h_wall - h_duct - h_wall;      // Vorderkante LED-Platte
y_f     = skin_t;                                // Vorderkante Halter
A_w = dsp[2] + 2 * h_wall;  A_h = dsp[3] + 2 * h_wall;
A_x0 = dsp[0] - A_w / 2;    A_z0 = dsp[1] - A_h / 2;
B_w = h_bw + 2 * h_wall;
B_z1 = dsp[1] + led_h / 2 + h_wall;
B_z0 = z_body0 + mm(0.3);                        // Halter schwebt über dem Bodenloch

// Deckel
cf = mm(canopy_front_m);  ov = mm(canopy_side_m);
pin_d   = mm(pin_d_m);   pin_len = mm(pin_len_m);   pin_x = mm(pin_x_m);
hole_d  = mm(pin_d_m + 2 * pin_clear_m);   hole_depth = mm(hole_depth_m);
th = mm(plug_h_m);  tw = mm(plug_wall_m);  tc = mm(plug_clear_m);
ring_x0 = wall + tc;           ring_x1 = W - wall - tc;
ring_y0 = tf + lip + tc;       ring_y1 = D - tb - lip - tc;

// Farben (nur Vorschau)
c_core = "#5a5f68"; c_yellow = "#FDB913"; c_white = "#F2F2F2";
c_black = "#1a1a1a"; c_back = "#d8d8d8";

// ---------------------------------------------------------------
//  Post-Logo (aus der gelieferten PNG vektorisiert), Einheit: Bild-Pixel
//  Ursprung = links oben, y nach unten negativ
// ---------------------------------------------------------------
LOGO_W    = 2554;
LOGO_PTS  = [
    [627.0,-32.0],
    [80.0,-32.0],
    [59.0,-36.0],
    [40.0,-44.0],
    [22.0,-58.0],
    [8.0,-78.0],
    [1.0,-100.0],
    [0.0,-125.0],
    [6.0,-152.0],
    [16.0,-172.0],
    [343.0,-662.0],
    [343.0,-594.0],
    [345.0,-565.0],
    [357.0,-481.0],
    [378.0,-399.0],
    [391.0,-361.0],
    [413.0,-308.0],
    [438.0,-258.0],
    [459.0,-222.0],
    [507.0,-153.0],
    [546.0,-107.0],
    [589.0,-64.0],
    [92.0,-114.0],
    [441.0,-114.0],
    [409.0,-154.0],
    [388.0,-185.0],
    [364.0,-226.0],
    [343.0,-269.0],
    [324.0,-317.0],
    [310.0,-362.0],
    [302.0,-395.0],
    [293.0,-447.0],
    [86.0,-129.0],
    [85.0,-123.0],
    [87.0,-118.0],
    [525.0,-889.0],
    [555.0,-956.0],
    [576.0,-993.0],
    [597.0,-1025.0],
    [638.0,-1077.0],
    [684.0,-1124.0],
    [727.0,-1160.0],
    [773.0,-1192.0],
    [809.0,-1213.0],
    [847.0,-1232.0],
    [885.0,-1248.0],
    [956.0,-1271.0],
    [1021.0,-1285.0],
    [1088.0,-1293.0],
    [1168.0,-1295.0],
    [1244.0,-1291.0],
    [1306.0,-1283.0],
    [1371.0,-1269.0],
    [1446.0,-1245.0],
    [1509.0,-1218.0],
    [1573.0,-1184.0],
    [1641.0,-1141.0],
    [1699.0,-1099.0],
    [1766.0,-1045.0],
    [1837.0,-982.0],
    [1872.0,-949.0],
    [1980.0,-840.0],
    [2089.0,-721.0],
    [2207.0,-584.0],
    [2383.0,-368.0],
    [2522.0,-190.0],
    [2542.0,-161.0],
    [2552.0,-136.0],
    [2554.0,-108.0],
    [2548.0,-83.0],
    [2538.0,-65.0],
    [2523.0,-50.0],
    [2501.0,-38.0],
    [2474.0,-32.0],
    [1832.0,-32.0],
    [1458.0,-608.0],
    [1403.0,-689.0],
    [1358.0,-747.0],
    [1333.0,-775.0],
    [1304.0,-803.0],
    [1272.0,-828.0],
    [1249.0,-842.0],
    [1218.0,-856.0],
    [1190.0,-864.0],
    [1155.0,-869.0],
    [1117.0,-869.0],
    [1085.0,-865.0],
    [1057.0,-858.0],
    [1031.0,-848.0],
    [1008.0,-836.0],
    [984.0,-819.0],
    [960.0,-796.0],
    [943.0,-774.0],
    [928.0,-747.0],
    [917.0,-718.0],
    [911.0,-692.0],
    [908.0,-666.0],
    [908.0,-631.0],
    [912.0,-598.0],
    [919.0,-570.0],
    [928.0,-546.0],
    [943.0,-518.0],
    [959.0,-496.0],
    [985.0,-470.0],
    [1010.0,-452.0],
    [1035.0,-439.0],
    [1059.0,-430.0],
    [1089.0,-423.0],
    [1116.0,-420.0],
    [1147.0,-420.0],
    [1179.0,-424.0],
    [1200.0,-429.0],
    [1228.0,-439.0],
    [1249.0,-449.0],
    [1278.0,-467.0],
    [1309.0,-492.0],
    [1339.0,-523.0],
    [1567.0,-177.0],
    [1538.0,-148.0],
    [1503.0,-119.0],
    [1461.0,-90.0],
    [1430.0,-72.0],
    [1389.0,-52.0],
    [1343.0,-34.0],
    [1300.0,-21.0],
    [1256.0,-11.0],
    [1210.0,-4.0],
    [1159.0,-0.0],
    [1100.0,-0.0],
    [1069.0,-2.0],
    [1019.0,-8.0],
    [977.0,-16.0],
    [931.0,-28.0],
    [884.0,-44.0],
    [844.0,-61.0],
    [812.0,-77.0],
    [768.0,-103.0],
    [722.0,-136.0],
    [674.0,-178.0],
    [633.0,-222.0],
    [597.0,-269.0],
    [563.0,-324.0],
    [532.0,-389.0],
    [510.0,-452.0],
    [493.0,-524.0],
    [485.0,-584.0],
    [482.0,-645.0],
    [484.0,-703.0],
    [492.0,-768.0],
    [505.0,-827.0],
    [600.0,-859.0],
    [583.0,-806.0],
    [570.0,-744.0],
    [564.0,-689.0],
    [563.0,-631.0],
    [567.0,-575.0],
    [575.0,-524.0],
    [588.0,-472.0],
    [608.0,-416.0],
    [634.0,-362.0],
    [666.0,-311.0],
    [698.0,-270.0],
    [744.0,-223.0],
    [787.0,-188.0],
    [826.0,-162.0],
    [883.0,-132.0],
    [909.0,-121.0],
    [966.0,-102.0],
    [1008.0,-92.0],
    [1052.0,-85.0],
    [1098.0,-81.0],
    [1164.0,-81.0],
    [1209.0,-85.0],
    [1241.0,-90.0],
    [1285.0,-100.0],
    [1346.0,-121.0],
    [1404.0,-150.0],
    [1441.0,-174.0],
    [1461.0,-190.0],
    [1323.0,-402.0],
    [1300.0,-386.0],
    [1270.0,-370.0],
    [1240.0,-358.0],
    [1201.0,-347.0],
    [1166.0,-341.0],
    [1141.0,-339.0],
    [1101.0,-340.0],
    [1056.0,-347.0],
    [1022.0,-357.0],
    [991.0,-370.0],
    [966.0,-384.0],
    [934.0,-407.0],
    [903.0,-437.0],
    [886.0,-458.0],
    [869.0,-484.0],
    [853.0,-516.0],
    [841.0,-549.0],
    [831.0,-593.0],
    [827.0,-633.0],
    [828.0,-678.0],
    [835.0,-723.0],
    [846.0,-760.0],
    [862.0,-796.0],
    [882.0,-828.0],
    [905.0,-856.0],
    [933.0,-882.0],
    [964.0,-904.0],
    [996.0,-921.0],
    [1036.0,-936.0],
    [1074.0,-945.0],
    [1119.0,-950.0],
    [1154.0,-950.0],
    [1192.0,-946.0],
    [1220.0,-940.0],
    [1259.0,-927.0],
    [1292.0,-911.0],
    [1322.0,-892.0],
    [1355.0,-866.0],
    [1397.0,-825.0],
    [1443.0,-770.0],
    [1483.0,-715.0],
    [1876.0,-113.0],
    [2460.0,-113.0],
    [2467.0,-119.0],
    [2467.0,-127.0],
    [2457.0,-142.0],
    [2315.0,-324.0],
    [2202.0,-464.0],
    [2039.0,-656.0],
    [1904.0,-803.0],
    [1781.0,-924.0],
    [1718.0,-980.0],
    [1659.0,-1028.0],
    [1593.0,-1076.0],
    [1536.0,-1112.0],
    [1470.0,-1147.0],
    [1416.0,-1170.0],
    [1354.0,-1190.0],
    [1306.0,-1201.0],
    [1244.0,-1210.0],
    [1179.0,-1214.0],
    [1102.0,-1213.0],
    [1038.0,-1206.0],
    [969.0,-1191.0],
    [920.0,-1175.0],
    [873.0,-1155.0],
    [820.0,-1126.0],
    [770.0,-1091.0],
    [734.0,-1060.0],
    [694.0,-1018.0],
    [663.0,-978.0],
    [627.0,-919.0]
  ];
LOGO_PATHS = [[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21],[22,23,24,25,26,27,28,29,30,31,32,33,34],[35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149],[150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251]];

logo_w  = 1185;       // Breite im Original (mm)
logo_x0 = 408;        // linke Kante ab Station links (mm)
logo_dz = 474;        // Abstand Logo-Oberkante unter Türbereich-Oberkante (mm)
k_px    = col_w / 181.4;     // mm pro Foto-Pixel (Foto-Raster)

// ---------------------------------------------------------------
//  Fugen
// ---------------------------------------------------------------
// Fugen: ya..yb = Tiefenbereich (y von der Frontfläche aus)
module cut_h(x0, w, z, ya, yb)
    translate([x0, ya, z - groove/2]) cube([w, yb - ya, groove]);

module cut_v(x, ya, yb)
    translate([x - groove/2, ya, z_body0]) cube([groove, yb - ya, H_door]);

module column_cuts(x0, w, hs, zs, ya, yb) {
    for (i = [1 : 1 : len(hs) - 1]) cut_h(x0, w, zs + sum_to(hs, i), ya, yb);
}

module groove_cuts(ya, yb) {
    for (b = col_bounds) cut_v(b, ya, yb);
    for (i = [0 : 1 : n_left - 1])
        column_cuts(i * col_w, col_w, left_cols[i], z_body0, ya, yb);
    for (i = [0 : 1 : n_right - 1])
        column_cuts(xL + term_w + i * col_w, col_w, right_cols[i], z_body0, ya, yb);
    column_cuts(xL, term_w, term_below, z_body0, ya, yb);
    column_cuts(xL, term_w, term_above, zone_hi, ya, yb);
}

// Fugen sind groove_d tief sichtbar; der Fugengrund (grau) kommt aus dem Kern:
// die Frontschicht wird an den Fugen komplett durchschnitten, der Kern füllt
// den Bereich groove_d .. skin_t mit grauem Material wieder auf.
module groove_skin_cut()  groove_cuts(-1, skin_t + 1);
module groove_fill()      groove_cuts(groove_d, skin_t + 0.01);

// ---------------------------------------------------------------
//  Schwarze Einlagen: Logo, Schrift, Linien, Scheiben, Terminal-Blende
// ---------------------------------------------------------------
function P(x, y) = [x, -y];

module text_px() {
    translate(P(240, 325)) text("Post-",   size = 33, font = "Liberation Sans:style=Bold");
    translate(P(240, 372)) text("Station", size = 33, font = "Liberation Sans:style=Bold");
}
module rules_px() {
    for (r = [[240, 395], [406, 578], [590, 760], [772, 925]])
        translate(P(r[0], 278)) square([r[1] - r[0], 8]);
}
module discs_px() {
    for (d = [[673, 322, "L"], [493, 763, "M"], [857, 622, "S"]])
        translate(P(d[0], d[1])) difference() {
            circle(20, $fn = 40);
            text(d[2], size = 19, halign = "center", valign = "center",
                 font = "Liberation Sans:style=Bold");
        }
}

module art_model_2d() {
    translate([-220 * k_px, z_body1 + 242 * k_px]) scale(k_px) {
        text_px(); rules_px(); discs_px();
    }
    translate([logo_x0, z_body1 - logo_dz]) scale(logo_w / LOGO_W)
        polygon(points = LOGO_PTS, paths = LOGO_PATHS);
}

// Volumen der Einlage: y von -ext bis d (bündig mit Frontfläche y = 0)
module black_art_vol(d, ext = 1)
    translate([0, d, 0]) rotate([90, 0, 0])
        linear_extrude(height = d + ext, convexity = 10) art_model_2d();

module term_panel_vol(ext = 1)
    translate([xL + groove/2, -ext, zone_lo])
        cube([term_w - groove, skin_t + ext, zone_h]);

module window_cut()
    translate([dsp[0] - dsp[2]/2, -1, dsp[1] - dsp[3]/2])
        cube([dsp[2], skin_t + 2, dsp[3]]);

module scanner_cut()
    translate([scn[0] - scn[2]/2, -1, scn[1] - scn[3]/2])
        cube([scn[2], scn_depth + 1, scn[3]]);

// ---------------------------------------------------------------
//  Frontschichten (je ein Filament)
// ---------------------------------------------------------------
split_x = right_side_white ? xL : W;

module skin_zone(x0, x1) {
    if (x1 > x0)
        difference() {
            translate([x0, 0, z_body0]) cube([x1 - x0, skin_t, H_door]);
            groove_skin_cut();
            black_art_vol(skin_t, 1);
            term_panel_vol(1);
        }
}

module display_part()
    translate([dsp[0] - dsp[2]/2, 0, dsp[1] - dsp[3]/2])
        cube([dsp[2], skin_t, dsp[3]]);

module skin_yellow() skin_zone(0, split_x);

module skin_white() {
    skin_zone(split_x, W);
    display_part();
}

module logo_part()
    difference() { black_art_vol(skin_t, 0); groove_skin_cut(); }

module panel_part()
    difference() { term_panel_vol(0); window_cut(); scanner_cut(); }

module skin_black() {
    logo_part();
    panel_part();
}

// ---------------------------------------------------------------
//  Sockel (schwarz), Rahmenwände (grau), Front (grauer Träger)
// ---------------------------------------------------------------
module pin_hole(xx, yy)      // Loch für Führungsstift (von der Oberkante aus)
    translate([xx, yy, z_head1 - hole_depth])
        cylinder(d = hole_d, h = hole_depth + 1, $fn = 32);

// Magnettasche von oben; der Boden bleibt geschlossen; 3 Quetschrippen
module magnet_pocket(mx)
    translate([mx, D/2, mm(mag_floor_m)])
        difference() {
            cylinder(d = mag_pocket_d, h = H_plinth - mm(mag_floor_m) + 1, $fn = 64);
            for (a = [0, 120, 240]) rotate([0, 0, a])
                translate([mag_pocket_d/2 - mm(mag_rib_m), -mm(0.3), -1])
                    cube([mm(mag_rib_m) + mm(0.3), mm(0.6), H_plinth + 2]);
        }

// Der Magnet ragt über den Sockel hinaus: runde Aussparung in Front/Rückseite
module magnet_notch()
    for (mx = mag_x)
        translate([mx, D/2, z_body0 - 1])
            cylinder(d = mag_notch_d, h = mag_top + mm(0.4) - (z_body0 - 1), $fn = 64);

module sockel_raw() {
    difference() {
        cube([W, D, H_plinth]);                      // volle Tiefe
        // Bodenloch für 4-poligen JST-Stecker (Mitte)
        translate([W/2 - mm(jst_w_m)/2, D/2 - mm(jst_h_m)/2, -1])
            cube([mm(jst_w_m), mm(jst_h_m), H_plinth + 2]);
        for (mx = mag_x) magnet_pocket(mx);
    }
}

module frame_walls() {
    for (x0 = [0, W - wall])
        translate([x0, tf, H_plinth]) cube([wall, D - tf - tb, z_head1 - H_plinth]);
}

// Front: grauer Träger + Kopfleiste + Steckrand (Farbschicht kommt als skin_*)
module front_core() {
    difference() {
        union() {
            translate([0, skin_t, z_body0]) cube([W, tf - skin_t, H_door]);       // Träger
            translate([0, 0, z_body1 - 0.01]) cube([W, tf, H_header + 0.01]);      // Kopfleiste
            translate([wall + fit, tf - 0.01, H_plinth + fit])                      // Steckrand
                cube([W - 2*wall - 2*fit, lip + 0.01, z_head1 - (H_plinth + fit)]);
            groove_fill();                                                          // grauer Fugengrund
        }
        // Öffnung für den LED-Halter hinter dem Display
        translate([A_x0 - clh, skin_t - 1, A_z0 - clh])
            cube([A_w + 2*clh, tf + lip - skin_t + 2, A_h + 2*clh]);
        // Kopfleiste segmentiert
        for (b = col_bounds)
            translate([b - groove/2, -1, z_body1]) cube([groove, groove_d + 1, H_header + 1]);
        // Löcher für die Führungsstifte des Deckels
        for (xx = [pin_x, W - pin_x]) pin_hole(xx, (tf + lip) / 2);
        magnet_notch();
    }
}

// ---------------------------------------------------------------
//  Rückseite (Steckrand, Lüftungsschlitze)
// ---------------------------------------------------------------
module back_vents() {
    y0 = D - mm(vent_depth_m);
    gx = [xL / 2, W - n_right * col_w / 2];
    for (x = gx) for (z0 = vent_z) for (r = [0 : vent_rows - 1])
        translate([x - vent_len/2, y0,
                   z0 + (r - (vent_rows - 1)/2) * vent_pitch - mm(vent_h_m)/2])
            cube([vent_len, D + 1 - y0, mm(vent_h_m)]);
}

module back_raw() {
    difference() {
        union() {
            translate([0, D - tb, z_body0]) cube([W, tb, z_head1 - z_body0]);     // Flansch
            translate([wall + fit, D - tb - lip, H_plinth + fit])                  // Steckrand
                cube([W - 2*wall - 2*fit, lip + 0.01, z_head1 - (H_plinth + fit)]);
        }
        back_vents();
        for (xx = [pin_x, W - pin_x]) pin_hole(xx, D - (tb + lip) / 2);
        magnet_notch();
    }
}

// ---------------------------------------------------------------
//  LED-Halter Display: Lichtkasten + Kabelschacht (nach unten offen)
// ---------------------------------------------------------------
module led_holder() {
    d = dsp;
    difference() {
        union() {
            translate([A_x0, y_f, A_z0]) cube([A_w, y_pl + h_wall - y_f, A_h]);
            translate([d[0] - B_w/2, y_pl, B_z0]) cube([B_w, y_end - y_pl, B_z1 - B_z0]);
        }
        // Lichtkammer (zur Display-Fläche offen)
        translate([d[0] - d[2]/2, y_f - 1, d[1] - d[3]/2])
            cube([d[2], y_pl - y_f + 1, d[3]]);
        // LED-Schlitz in der Platte
        translate([d[0] - led_w/2, y_pl - 1, d[1] - led_h/2])
            cube([led_w, h_wall + 2, led_h]);
        // Kabelschacht hinter der Platte, unten offen
        translate([d[0] - h_bw/2, y_pl + h_wall, B_z0 - 1])
            cube([h_bw, h_duct, (d[1] + led_h/2) - B_z0 + 1]);
    }
}

// ---------------------------------------------------------------
//  Deckel mit Überstand, innenliegendem Kabelkanal und Steckrahmen
// ---------------------------------------------------------------
module guide_pins() {        // 4 Führungsstifte mit angespitzter Kuppe
    for (xx = [pin_x, W - pin_x]) for (yy = [(tf + lip) / 2, D - (tb + lip) / 2])
        translate([xx, yy, z_head1 - pin_len]) {
            cylinder(d1 = pin_d * 0.6, d2 = pin_d, h = mm(0.3), $fn = 32);
            translate([0, 0, mm(0.3)])
                cylinder(d = pin_d, h = pin_len - mm(0.3) + 0.01, $fn = 32);
        }
}

module plug_ring() {
    bump = mm(plug_bump_m);  bw = mm(0.6);
    translate([0, 0, z_head1 - th]) {
        difference() {
            translate([ring_x0, ring_y0, 0])
                cube([ring_x1 - ring_x0, ring_y1 - ring_y0, th + 0.01]);
            translate([ring_x0 + tw, ring_y0 + tw, -1])
                cube([ring_x1 - ring_x0 - 2*tw, ring_y1 - ring_y0 - 2*tw, th + 2]);
        }
        // Klemmnoppen
        for (x = [W*0.2, W*0.4, W*0.6, W*0.8])
            translate([x - bw/2, ring_y0 - bump, mm(0.2)])
                cube([bw, bump + 0.1, th - mm(0.4)]);
        for (xx = [ring_x0 - bump, ring_x1 - 0.1])
            translate([xx, (ring_y0 + ring_y1)/2 - bw/2, mm(0.2)])
                cube([bump + 0.1, bw, th - mm(0.4)]);
    }
}

// Gerader Kabelkanal zwischen p0 und p1 (x/y), innen im Deckel.
// Querschnitt "Haus auf dem Kopf": das Dach zeigt zur Deckel-Unterseite und
// hat 45 Grad -> beim Druck (Deckel auf dem Kopf) selbsttragend, KEINE Stützen.
module cable_tunnel(p0, p1) {
    cw = mm(can_ch_w_m);
    zf = mm(can_ch_z1_m);                  // Kanal-Oberkante
    zk = zf - mm(can_ch_wall_m);           // Beginn des 45-Grad-Dachs
    za = zk - cw / 2;                      // Dachspitze
    dx = p1[0] - p0[0];  dy = p1[1] - p0[1];
    L  = sqrt(dx*dx + dy*dy);
    a  = atan2(dy, dx);
    translate([p0[0], p0[1], z_head1]) rotate([0, 0, a]) rotate([90, 0, 90])
        linear_extrude(height = L, convexity = 4)
            polygon([[-cw/2, zf], [cw/2, zf], [cw/2, zk], [0, za], [-cw/2, zk]]);
}

module canopy_raw() {
    yl = -cf / 2;           yc = D / 2;
    lx = [W/2 - canopy_led_dx, W/2 + canopy_led_dx];     // mittig zur Station
    difference() {
        union() {
            translate([-ov, -cf, z_head1]) cube([W + 2*ov, D + cf + ov, canopy_h]);
            plug_ring();
            guide_pins();
        }
        for (x = lx) {
            // LED-Tasche (1206) an der Unterseite
            translate([x - led_w/2, yl - led_h/2, z_head1 - 1])
                cube([led_w, led_h, mm(can_pocket_m) + 1]);
            // gerader Kanal rechtwinklig von der LED nach hinten (+y)
            cable_tunnel([x, yl], [x, yc]);
            // großer Auslass nach unten in die Station
            translate([x - mm(can_open_w_m)/2, yc - mm(can_open_d_m)/2, z_head1 - 1])
                cube([mm(can_open_w_m), mm(can_open_d_m), mm(1.4) + 1]);
        }
    }
}

// ---------------------------------------------------------------
//  Druckausrichtung
// ---------------------------------------------------------------
module orient_front()        // Front (y = 0) nach oben: Platte liegt auf dem Rücken
    if (print_layout) translate([0, 0, tf + lip]) rotate([-90, 0, 0]) children();
    else children();

module orient_back()         // Außenseite auf dem Druckbett, Steckrand oben
    if (print_layout) translate([0, 0, D]) rotate([-90, 0, 0]) children();
    else children();

module orient_frame()        // Rahmen steht aufrecht (Sockel auf dem Bett), keine Stützen nötig
    children();

module orient_canopy()       // Deckel auf den Kopf: Oberseite auf dem Druckbett
    if (print_layout) translate([0, D + ov, z_head1 + canopy_h]) rotate([180, 0, 0]) children();
    else children();

module orient_holder()       // Halter mit offener Front auf dem Druckbett
    if (print_layout)
        translate([-(dsp[0] - B_w/2), A_z0 + A_h, -y_f]) rotate([90, 0, 0]) children();
    else children();

// ---------------------------------------------------------------
//  Ausgabe
// ---------------------------------------------------------------
scale(S) {
    if (part == "all") {
        color(c_core)   front_core();
        color(c_yellow) skin_yellow();
        color(c_white)  skin_white();
        color(c_black)  skin_black();
        color(c_black)  sockel_raw();
        color(c_core)   frame_walls();
        color(c_core)   canopy_raw();
        color(c_black)  led_holder();
        if (show_back) color(c_back) back_raw();
    }
    else if (part == "front_core")  orient_front() front_core();
    else if (part == "skin_yellow") orient_front() skin_yellow();
    else if (part == "skin_white")  orient_front() skin_white();
    else if (part == "skin_black")  orient_front() skin_black();
    else if (part == "frame_base")  orient_frame() sockel_raw();
    else if (part == "frame_walls") orient_frame() frame_walls();
    else if (part == "back")        orient_back() back_raw();
    else if (part == "canopy")      orient_canopy() canopy_raw();
    else if (part == "led_holder")  orient_holder() led_holder();
}

echo(str("Original: ", W, " x ", D, " x ", H_total, " mm"));
echo(str("Modell 1:", scale_divisor, ": ",
         round(W*S*100)/100, " x ", round(D*S*100)/100, " x ",
         round(H_total*S*100)/100, " mm"));
