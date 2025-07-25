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

        static void Main(string[] args)
        {
            int result = AddNumbers(5, 7);
            Console.WriteLine($"5 + 7 = {result}");

            Console.WriteLine("Calling OpenCL...");
            QueryOpenCL();
        }
    }
}  // namespace ConsoleApp