using System;
using System.Runtime.InteropServices;

namespace PInvokeGUI
{
    public static class NativeMethods
    {
        [DllImport("libnative.dylib", EntryPoint = "times2_to_array_elements")]
        public static extern void Times2ToArrayElements(float[] data, int length);
    }
}
