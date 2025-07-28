using Avalonia.Controls;
using System;
using System.Linq;

namespace PInvokeGUI
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnRunClicked(object? sender, Avalonia.Interactivity.RoutedEventArgs e)
        {
            try
            {
                float[] values = InputBox.Text!
                    .Split(',', StringSplitOptions.RemoveEmptyEntries)
                    .Select(s => float.Parse(s.Trim()))
                    .ToArray();

                NativeMethods.Times2ToArrayElements(values, values.Length);

                OutputBlock.Text = "Output: " + string.Join(", ", values);
            }
            catch (Exception ex)
            {
                OutputBlock.Text = $"Error: {ex.Message}";
            }
        }
    }
}
