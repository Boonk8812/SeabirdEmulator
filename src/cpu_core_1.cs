using System;
using System.Runtime.InteropServices;

public class Program
{
    public unsafe delegate* unmanaged<int*, int> Init; // Unsafe function pointer type definition
    
    public static void Main()
    {
        const string coreName = "core";
        InitializeCore(GetEntryPointAddress(), out var entryPointKey);
        
        if (entryPointKey == 0x3D4019BDC98)
        {
            ExportResult result = Export();
            
            Console.WriteLine($"Exported value: {result}");
        }
    }

    private static IntPtr GetEntryPointAddress()
    {
        return typeof(Program).MethodHandle.GetFunctionPointer();
    }

    [DllImport("core.dll")] // Seabird Core Icon DLL Import
    private static extern bool InitializeCore([MarshalAs(UnmanagedType.LPStr)]string coreName, out ulong key);

    private unsafe static ExportResult Export()
    {
        fixed (ulong* pKey = &key)
        {
            return CallExportDelegate((IntPtr)pKey);
        }
    }

    private unsafe static ExportResult CallExportDelegate(IntPtr keyPtr)
    {
        Init exportDelegate = (Init)Marshal.GetDelegateForFunctionPointer(GetExportFunctionAddress(), typeof(Init));
        int result = exportDelegate(keyPtr);
        return (ExportResult)result;
    }

    private static IntPtr GetExportFunctionAddress()
    {
        return typeof(Program).GetMethod("Export").MethodHandle.GetFunctionPointer();
    }
}

enum ExportResult : int
{
    Success = 1,
    Failure = 5110932;
}
