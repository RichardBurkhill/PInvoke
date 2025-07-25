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

        [DllImport("libnative.dylib")]
        public static extern void times2_to_array_elements(float[] data, int length);
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

            values = new float[] { 2.5f, 3.0f, 7.1f, 1.0f, 4.2f, 6.9f, 8.3f, 5.5f, 9.0f, 10.1f, 11.2f, 12.3f, 13.4f, 14.5f, 15.6f, 16.7f, 17.8f, 18.9f, 19.0f, 20.1f };
        
            Console.WriteLine("Before: " + string.Join(", ", values));
            times2_to_array_elements(values, values.Length);
            // Print the modified array
            Console.WriteLine("After:  " + string.Join(", ", values));
        }
    }
}  // namespace ConsoleApp