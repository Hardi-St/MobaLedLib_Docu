using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

/*
MLLSimulator: A LED simulator for MobaLedLib library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Copyright(C) 2022  Jürgen Winkler : MobaLedLib@gmx.at

This library is free software; you can redistribute itand /or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301 USA
*/


namespace MLLSimulator
{
    public partial class LedForm : Form
    {
        const byte ledWidth = 20;

        List<Label> labels = new List<Label>();
        IntPtr ledsPtr; 

        public LedForm()
        {
            InitializeComponent();

            for (int x=0;x<8;x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    var l = new Label();
                    l.Location = new Point(100 + y * ledWidth, 10 + x * ledWidth);
                    l.AutoSize = false;
                    l.Size = new Size(ledWidth, ledWidth);
                    this.Controls.Add(l);
                    labels.Add(l);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MobaLedLib.SetInput(0, 1);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MobaLedLib.SetInput(0, 0);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                MobaLedLib.Update();

                for (byte i = 0; i < 64; i++)
                {
                    //int col = MobaLedLib.GetLedColor(i);
                    //labels[i].BackColor = Color.FromArgb(col&0xff, (col >> 8)&0xff, (col >> 16) & 0xff);
                    byte r, g, b;
                    r = Marshal.ReadByte(ledsPtr, i * 3);
                    g = Marshal.ReadByte(ledsPtr, i * 3 + 1);
                    b = Marshal.ReadByte(ledsPtr, i * 3 + 2);

                    r = ShiftColor(r);
                    g = ShiftColor(g);
                    b = ShiftColor(b);
                    //labels[i].BackColor = Color.FromArgb();
                    labels[i].BackColor = Color.FromArgb(r, g, b);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Exception " + ex.ToString(), "Timer execution failed");
                Application.Exit();
            }

        }

        private byte ShiftColor(byte color)
        {
            int offset = 70;
            if (color == 0) return 0;
            int newColor = color * (255 - offset);
            newColor /= 255;
            return (byte)(offset + newColor);
        }

        private void LedForm_Load(object sender, EventArgs e)
        {
            try
            {
                var config = File.ReadAllBytes(@".\LEDConfigWithFire.bin");
                ledsPtr = MobaLedLib.Create(config, config.Length);
                timer1.Interval = 20;
                timer1.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Exception " + ex.ToString(), "Program failed to start");
                Application.Exit();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MobaLedLib.ShowLEDWindow(16, 16, 32, 1, 100, 100, true);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            MobaLedLib.CloseLEDWindow();
        }
    }
}


/*
 * 
 * atemp=C:\Users\...\AppData\Local\Temp\MobaLedLib_build\ATMega
 * 
 * "%bin%\avr-readelf" -a "%atemp%\LEDs_AutoProg.ino.elf" 
 * 
 * Symbol table '.symtab' contains 323 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
   136: 000000e8   483 OBJECT  LOCAL  DEFAULT    2 _ZL6Config


   = Offset 0xe8 Len=0x1e3 im %atemp%\LEDs_AutoProg.ino.hex" 
   bzw. in LEDs_AutoProg.ino.with_bootloader.bin

"%aHome%\hardware\tools\avr\bin\avr-readelf" -a "%atemp%\LEDs_AutoProg.ino.elf" >"%atemp%\LEDs_AutoProg.ino.elf.txt"

*/