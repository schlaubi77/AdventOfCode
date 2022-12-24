using System.Text;

class Part2
{
    static void Main(string[] args)
    {
        string[] read = File.ReadAllLines("..\\input.txt", Encoding.UTF8);

        int[][] sensors = new int[read.Length][]; // 3 entries: x, y, distance to next beacon

        for (int i = 0; i < read.Length; i++)
        {
            string[] numbers = read[i].Replace("Sensor at x=", "").Replace("y=", "").Replace(",", "").Replace(": closest beacon is at", "").Replace("x=", "").Split(" ");
            int[] entry = new int[3];
            entry[0] = int.Parse(numbers[0]);
            entry[1] = int.Parse(numbers[1]);
            entry[2] = Math.Abs(entry[0] - int.Parse(numbers[2])) + Math.Abs(entry[1] - int.Parse(numbers[3]));
            sensors[i] = entry;
        }

        foreach (int[] sensor in sensors)
        {
            for(int offsetX = -sensor[2]; offsetX <= sensor[2]; offsetX++)
            {
                if (sensor[0] + offsetX >= 4_000_001 || sensor[0] + offsetX < -1)
                    continue;

                int offsetY = sensor[2] - Math.Abs(offsetX);
                if (sensor[1] + offsetY <= 4_000_001 && sensor[1] + offsetY > -1)
                {
                    // check outer side
                    if (!isCovered(sensor[0] + offsetX + 1, sensor[1] + offsetY, sensors))
                    {
                        Console.WriteLine((sensor[0] + offsetX + 1) * 4_000_000L + (sensor[1] + offsetY));
                        return;
                    }
                    if (offsetX > 0)
                    {
                        // check up
                        
                        if (!isCovered(sensor[0] + offsetX, sensor[1] + offsetY + 1, sensors))
                        {
                            Console.WriteLine((sensor[0] + offsetX) * 4_000_000L + (sensor[1] + offsetY + 1));
                            return;
                        }
                    }
                    else
                    {
                        // check down
                        if (!isCovered(sensor[0] + offsetX, sensor[1] + offsetY - 1, sensors))
                        {
                            Console.WriteLine((sensor[0] + offsetX) * 4_000_000L + (sensor[1] + offsetY - 1));
                            return;
                        }
                    }

                }

                if (sensor[1] - offsetY <= 4_000_001 && sensor[1] - offsetY > -1)
                {
                    // check outer side
                    if (!isCovered(sensor[0] + offsetX - 1, sensor[1] - offsetY, sensors))
                    {
                        Console.WriteLine((sensor[0] - offsetX - 1) * 4_000_000L + (sensor[1] - offsetY));
                        return;
                    }

                    if(offsetX > 0)
                    {
                        // check up
                        if (!isCovered(sensor[0] + offsetX, sensor[1] - offsetY + 1, sensors))
                        {
                            Console.WriteLine((sensor[0] + offsetX) * 4_000_000L + (sensor[1] - offsetY + 1));
                            return;
                        }
                    }
                    else
                    {
                        // check down
                        if (!isCovered(sensor[0] + offsetX, sensor[1] - offsetY - 1, sensors))
                        {
                            Console.WriteLine((sensor[0] + offsetX) * 4_000_000L + (sensor[1] - offsetY - 1));
                            return;
                        }
                    }
                }
            }
        }
    }

    private static bool isCovered(int posX, int posY, int[][] sensors)
    {
        foreach (int[] sensor in sensors)
        {
            if(Math.Abs(posX - sensor[0]) + Math.Abs(posY - sensor[1]) <= sensor[2])
            {
                return true;
            }
        }
        return false;
    }
}