using System.Text;

class Part1
{
    static void Main(string[] args)
    {
        string[] read = File.ReadAllLines("..\\input.txt", Encoding.UTF8);

        int[][] sensors = new int[read.Length][]; // 3 entries: x, y, distance to next beacon

        int highestX = 0;
        int lowestX = int.MaxValue;
        int highestDistance = 0;

        for (int i = 0; i < read.Length; i++)
        {
            string[] numbers = read[i].Replace("Sensor at x=", "").Replace("y=", "").Replace(",", "").Replace(": closest beacon is at", "").Replace("x=", "").Split(" ");
            int[] entry = new int[3];
            entry[0] = int.Parse(numbers[0]);
            entry[1] = int.Parse(numbers[1]);
            entry[2] = Math.Abs(entry[0] - int.Parse(numbers[2])) + Math.Abs(entry[1] - int.Parse(numbers[3]));
            sensors[i] = entry;
            
            highestX = Math.Max(highestX, entry[0]);
            lowestX = Math.Min(lowestX, entry[0]);
            highestDistance = Math.Max(highestDistance, entry[2]);
        }

        int cannotContain = -1; // I have to start at -1 for some reason

        for (int i = lowestX - highestDistance; i <= highestX + highestDistance; i++)
        {
            foreach (int[] sensor in sensors)
            {
                if(Math.Abs(i - sensor[0]) + Math.Abs(2000000 - sensor[1]) <= sensor[2])
                {
                    cannotContain++;
                    break;
                }
            }
        }

        Console.WriteLine(cannotContain);
    }
}