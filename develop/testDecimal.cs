using System;
using System.Globalization;
using System.Linq;

public class DecimalCalculations
{
    public static void Main(string[] args)
    {
        bool error = false;
        while (!error)
        {
            try
            {
                decimal res = 0;
                if (DoOperations(ref res))
                {
                    string strResult = DecimalToBitString(res);
                    decimal decimalValue = StringToDecimal(strResult);
                    Console.WriteLine("\n---Input myResult:---");
                    decimal myResult = InputDecimal();
                    Console.WriteLine("\n---RIGHT RESULT INFO---");
                    DecimalInfoOutput(decimalValue);
                    Console.WriteLine("\n---MY RESULT INFO---");
                    DecimalInfoOutput(myResult);
                    CompareResults(strResult, DecimalToBitString(myResult));
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                error = true;
            }
        }
    }

    public static void CompareResults(string rightResult, string myResult)
    {
        if (rightResult == myResult)
        {
            Console.WriteLine("\nTEST IS OK\n");
        }
        else
        {
            PrintDifference(rightResult, myResult);
            Console.WriteLine("\nTEST IS FAILED!!\n");
        }
    }
    public static void PrintDifference(string rightResult, string myResult)
    {
        int countOfErrors = 0;
        Console.WriteLine("Right result:");
        Console.WriteLine(rightResult);

        Console.WriteLine("My result:");
        Console.WriteLine(myResult);

        Console.WriteLine("Diff:");
        for (int i = 0; i < rightResult.Length; i++)
        {
            if (rightResult[i] != myResult[i])
            {
                Console.Write('1');
                countOfErrors++;
            }
            else if (rightResult[i] == '1' || rightResult[i] == '0')
            {
                Console.Write('0');
            }
            else
            {
                Console.Write(rightResult[i]);
            }
        }

        Console.WriteLine($"\nErrors count: {countOfErrors}\n");
    }
    public static void DecimalInfoOutput(decimal value)
    {
        Console.WriteLine($"In decimal: {value}");
        int[] parts = decimal.GetBits(value);
        int sign = Convert.ToInt32((parts[3] & 0x80000000) != 0);
        byte scale = (byte)((parts[3] >> 16) & 0x7F);
        Console.WriteLine($"Sign = {sign}, scale = {scale}");
        Console.WriteLine("BITS:");
        for (int i = 3; i >= 0; i--)
        {
            Console.WriteLine($"bits[{i}]={(uint)parts[i]}");
        }
    }
    public static decimal InputDecimal()
    {
        bool isNumInputedCorrectly = false, isModeInputedCorrectly = false;
        decimal value = 0;
        int mode = 0;
        while (!isModeInputedCorrectly)
        {
            try
            {
                Console.WriteLine("\n-------\nInput number\n0 - in bynary, 1 - in decimal (10 base)");
                mode = Convert.ToInt32(Console.ReadLine());
                isModeInputedCorrectly = true;
            }
            catch { Console.WriteLine("Wrong input, try again"); }
        }
        while (!isNumInputedCorrectly)
        {
            try
            {
                if (mode == 0)
                    value = InputDecimalFromString();
                else
                    value = InputDecimalFromArr();
                isNumInputedCorrectly = true;
            }
            catch (Exception e) { Console.WriteLine($"Wrong input, try again: {e.ToString()}"); }
        }
        return value;
    }
    public static int InputInt()
    {
        bool isNumInputedCorrectly = false;
        int value = 0;
        Console.WriteLine("\n-------\nInput number");
        while (!isNumInputedCorrectly)
        {
            try
            {
                value = Convert.ToInt32(Console.ReadLine());
                isNumInputedCorrectly = true;
            }

            catch { Console.WriteLine("Wrong input, try again"); }
        }
        return value;
    }
    public static float InputFloat()
    {
        bool isNumInputedCorrectly = false;
        float value = 0;
        Console.WriteLine("\n-------\nInput number");
        while (!isNumInputedCorrectly)
        {
            try
            {
                value = float.Parse(Console.ReadLine(), CultureInfo.InvariantCulture.NumberFormat);
                isNumInputedCorrectly = true;
            }
            catch { Console.WriteLine("Wrong input, try again"); }
        }
        return value;
    }
    public static decimal InputDecimalFromString()
    {
        Console.WriteLine("Input number in form [...][...][...][...]");
        decimal decimalValue = StringToDecimal(Console.ReadLine());
        return decimalValue;
    }
    public static decimal InputDecimalFromArr()
    {
        Console.WriteLine("Input via: 0 - sign and scale, 1 - bits[3]");
        bool sign;
        byte scale;
        uint bits3 = 0;
        if (Convert.ToInt32(Console.ReadLine()) == 0)
        {
            Console.WriteLine("Input sign (0-1)");
            sign = Convert.ToBoolean(Convert.ToInt32(Console.ReadLine()));
            Console.WriteLine("Input scale (0-28)");
            scale = Convert.ToByte(Console.ReadLine());
        }
        else
        {
            Console.WriteLine("Input bits[3]");
            bits3 = Convert.ToUInt32(Console.ReadLine());
            sign = GetSign(bits3);
            scale = GetScale(bits3);
        }
        uint[] parts = new uint[3];
        for (int i = 2; i >= 0; i--)
        {
            Console.WriteLine($"Input bits[{i}]");
            parts[i] = Convert.ToUInt32(Console.ReadLine());
        }
        decimal value = new Decimal((int)parts[0], (int)parts[1], (int)parts[2], sign, scale);
        Console.WriteLine($"Value in decimal: {value}");
        Console.WriteLine(DecimalToBitString(value));
        return value;
    }
    /// <summary>
    /// provides operations with decimal type
    /// </summary>
    /// <param name="decimalRes"></param>
    /// <returns>is result a decimal</returns>
    public static bool DoOperations(ref decimal decimalRes)
    {
        bool isResDecimal = true, isInputError = true;
        int mode = 0;
        while (isInputError)
        {
            try
            {
                Console.WriteLine("\nChoose, 0 - arithmetic, 1 - rounding, 2 - converting 3 - input num");
                mode = Convert.ToInt32(Console.ReadLine());
                isInputError = false;
            }
            catch
            {
                Console.WriteLine("Error: wrong input. Try again");
            }
        }

        if (mode == 0)
        {
            Console.WriteLine("Choose, 0 +, 1 -, 2 *, 3 /, 4 - negate");
            decimalRes = DoArithmeticOperations(Convert.ToInt32(Console.ReadLine()));
        }
        else if (mode == 1)
        {
            Console.WriteLine("Choose, 0 - floor, 1 - truncate, 2 - round");
            decimalRes = DoRoudingOperations(Convert.ToInt32(Console.ReadLine()));
        }
        else if (mode == 2)
        {
            Console.WriteLine("Choose, 0 - from int, 1 - from float, 2 - to int, 3 - to float");
            int intRes = 0;
            float floatRes = 0;
            mode = Convert.ToInt32(Console.ReadLine());
            if (!DoConvertingOperations(mode, ref intRes, ref floatRes, ref decimalRes))
            {
                if (mode == 2)
                {
                    IntConversionResults(intRes);
                    isResDecimal = false;
                }
                else if (mode == 3)
                {
                    FloatConversionResults(floatRes);
                    isResDecimal = false;
                }
            }
            else Console.WriteLine("TEST IS FAILED. Error occured");
        }
        else if (mode == 3)
        {
            decimal value = InputDecimal();
            Console.WriteLine("\n---NUMBER INFO---");
            DecimalInfoOutput(value);
            isResDecimal = false;
        }
        else
            Console.WriteLine("Error: wrong mode input");
        return isResDecimal;
    }
    public static void IntConversionResults(int rightResult)
    {
        Console.WriteLine("\n---Input myResult:---");
        int myResult = InputInt();
        Console.WriteLine("---Right result---");
        Console.WriteLine(rightResult);
        if (rightResult == myResult) Console.WriteLine("\nTEST IS OK\n");
        else Console.WriteLine("\nTEST IS FAILED!!\n");
    }
    public static void FloatConversionResults(float rightResult)
    {
        Console.WriteLine("\n---Input myResult:---");
        float myResult = InputFloat();
        Console.WriteLine("---Right result---");
        Console.WriteLine(rightResult);
        if (rightResult == myResult) Console.WriteLine("\nTEST IS OK\n");
        else Console.WriteLine("\nTEST IS FAILED!!\n");
    }
    public static decimal DoArithmeticOperations(int mode)
    {
        decimal value1 = InputDecimal(), value2 = 0;
        if (mode !=4)
            value2 = InputDecimal();
        decimal res = 0;
        if (mode == 0)
            res = Decimal.Add(value1, value2);
        else if (mode == 1)
            res = Decimal.Subtract(value1, value2);
        else if (mode == 2)
            res = Decimal.Multiply(value1, value2);
        else if (mode == 3)
            res = Decimal.Divide(value1, value2);
        else if (mode == 4)
            res = Decimal.Negate(value1);
        else
            Console.WriteLine("Error: wrong input");
        return res;
    }
    public static decimal DoRoudingOperations(int mode)
    {
        decimal value1 = InputDecimal();
        decimal res = 0;
        if (mode == 0)
            res = Decimal.Floor(value1);
        else if (mode == 1)
            res = Decimal.Truncate(value1);
        else if (mode == 2)
            res = Decimal.Round(value1);
        else
            Console.WriteLine("Error: wrong input");
        return res;
    }
    public static bool DoConvertingOperations(int mode, ref int intValue, ref float floatValue, ref decimal decimalValue)
    {
        bool error = false;
        if (mode == 0)
        {
            decimalValue = Convert.ToDecimal(InputInt());
        }
        else if (mode == 1)
        {
            decimalValue = Convert.ToDecimal(InputFloat());
        }
        else if (mode == 2)
        {
            decimal temp = InputDecimal();
            if (temp <= int.MaxValue && temp >= int.MinValue)
                intValue = Convert.ToInt32(temp);
            else
            {
                Console.WriteLine("ERROR: too big or too small value");
                error = true;
            }
        }
        else if (mode == 3)
        {
            decimal temp = InputDecimal();
            Console.WriteLine(temp);
            if (!float.TryParse(temp.ToString(), out floatValue))
            {
                Console.WriteLine("ERROR: too big or too small value");
                error = true;
            }
        }
        else
        {
            Console.WriteLine("Error: wrong input");
            error = true;
        }
        return error;
    }
    public static string DecimalToBitString(decimal value)
    {
        int[] bits = decimal.GetBits(value);
        return $"[{Convert.ToString(bits[3], 2).PadLeft(32, '0')}][{Convert.ToString(bits[2], 2).PadLeft(32, '0')}][{Convert.ToString(bits[1], 2).PadLeft(32, '0')}][{Convert.ToString(bits[0], 2).PadLeft(32, '0')}]";
    }
    public static Decimal StringToDecimal(string str)
    {
        int[] mas = StringToIntArr(str);
        return IntArrToDecimal(mas);
    }
    public static int[] StringToIntArr(string source)
    {
        int[] mas = source.Split(']')
            .SkipLast(1)
            .Select(x => Convert.ToInt32(x.Trim('['), 2))
            .ToArray();
        Array.Reverse(mas, 0, mas.Length);
        return mas;
    }
    public static bool GetSign(int bits3)
    {
        return (bits3 & 0x80000000) != 0;
    }
    public static byte GetScale(int bits3)
    {
        return (byte)((bits3 >> 16) & 0x7F);
    }


    public static bool GetSign(uint bits3)
    {
        return (bits3 & 0x80000000) != 0;
    }
    public static byte GetScale(uint bits3)
    {
        return (byte)((bits3 >> 16) & 0x7F);
    }
    public static Decimal IntArrToDecimal(int[] parts)
    {
        bool sign = GetSign(parts[3]);
        byte scale = GetScale(parts[3]);
        Decimal newValue = new Decimal(parts[0], parts[1], parts[2], sign, scale);
        return newValue;
    }
}
