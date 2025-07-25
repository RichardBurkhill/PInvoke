using System;
using System;
using System.Runtime.InteropServices;

namespace ConsoleApp
{
    class Program
    {
        // Import the native function from the shared library
        [DllImport("libnative.dylib", EntryPoint = "add_numbers")]
        public static extern int AddNumbers(int a, int b);

        // Import the native function from the shared library
        [DllImport("libnative.dylib", EntryPoint = "query_opencl")]
        public static extern void QueryOpenCL();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void CallbackDelegate(string message);

        [DllImport("libnative.dylib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void register_callback(CallbackDelegate callback);

        static void MyManagedCallback(string msg)
        {
            Console.WriteLine("C++ said: " + msg);
        }

        [DllImport("libnative.dylib")]
        public static extern void add1_to_array_elements(float[] data, int length);
        static void Main(string[] args)
        {
            // Register the managed callback with the native library
            register_callback(MyManagedCallback);

            int result = AddNumbers(5, 7);
            Console.WriteLine($"5 + 7 = {result}");

            Console.WriteLine("Calling OpenCL...");
            QueryOpenCL();

            float[] values = { 2.5f, 3.0f, 7.1f };
            Console.WriteLine("Before: " + string.Join(", ", values));
            add1_to_array_elements(values, values.Length);
            // Print the modified array
            Console.WriteLine("After:  " + string.Join(", ", values));
        }
    }
}  // namespace ConsoleApp