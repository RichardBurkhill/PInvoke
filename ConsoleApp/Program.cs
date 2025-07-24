using System;
using System;
using System.Runtime.InteropServices;

namespace ConsoleApp
{
    class Program
    {
        [DllImport("libnative.dylib", EntryPoint = "add_numbers")]
        public static extern int AddNumbers(int a, int b);

        static void Main(string[] args)
        {
            int result = AddNumbers(5, 7);
            Console.WriteLine($"5 + 7 = {result}");
        }
    }
}
