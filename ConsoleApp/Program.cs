using System;
using System;
using System.Runtime.InteropServices;

namespace ConsoleApp
{
    class Program
    {
        [DllImport("libnative.dylib", EntryPoint = "query_opencl")]
        public static extern void QueryOpenCL();

        static void Main(string[] args)
        {
            Console.WriteLine("Calling OpenCL...");
            QueryOpenCL();
        }
    }
}  // namespace ConsoleApp