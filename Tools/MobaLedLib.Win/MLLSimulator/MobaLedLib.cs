using System;
using System.Runtime.InteropServices;

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
    class MobaLedLib
    {
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static IntPtr Create(byte[] configData, int configLength);
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static IntPtr CreateEx(byte[] configData, int configLength, byte[] l2vData, int l2vLength);
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static void Update();
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static void SetInput(byte channel, byte on);
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static int GetLedColor(byte ledNr);
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static void ShowLEDWindow(byte ledsX, byte ledsY, byte ledSize, byte ledOffset, int windowPosX, int windowPosY, bool topmost);
        [DllImport(@"MobaLedLibWrapper.dll", CallingConvention = CallingConvention.StdCall)]
        extern public static void CloseLEDWindow();
    }
}
