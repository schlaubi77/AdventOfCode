﻿using System.Text;

class Part1
{
    static void Main(string[] args)
    {
        string[] read = File.ReadAllLines("..\\input.txt", Encoding.UTF8);

        int[,] cave = new int[1000, 200]; // 0: Air, 1: Stone, 2: Sand

        foreach(string line in read)
        {
            string[] coord = line.Split(" -> ");
            for(int j = 1; j < coord.Length; j++)
            {
                int currentX = int.Parse(coord[j].Split(',')[0]);
                int currentY = int.Parse(coord[j].Split(',')[1]);
                int previousX = int.Parse(coord[j - 1].Split(',')[0]);
                int previousY = int.Parse(coord[j - 1].Split(',')[1]);

                if (currentX != previousX)
                {
                    if (currentX - previousX < 0)
                    {
                        for (int x = 0; x >= currentX - previousX; x--)
                        {
                            cave[previousX + x, currentY] = 1;
                        }
                    }
                    else
                    {
                        for (int x = 0; x <= currentX - previousX; x++)
                        {
                            cave[previousX + x, currentY] = 1;
                        }
                    }
                } else 
                {   
                    if(currentY - previousY < 0)
                    {
                        for (int y = 0; y >= currentY - previousY; y--)
                        {
                            cave[currentX, previousY + y] = 1;
                        }
                    }
                    else
                    {
                        for (int y = 0; y <= currentY - previousY; y++)
                        {
                            cave[currentX, previousY + y] = 1;
                        }
                    }
                }
            }
        }

        int sandPlaced = 0;
        bool done = false;

        while(!done)
        {
            int sandX = 500;
            int sandY = 0;

            while (true)
            {
                // Console.WriteLine(sandX + "," + sandY);
                if(cave[sandX, sandY + 1] == 0)
                {
                    sandY++;
                } else if(cave[sandX - 1, sandY + 1] == 0)
                {
                    sandX--;
                    sandY++;
                } else if(cave[sandX + 1, sandY + 1] == 0)
                {
                    sandX++;
                    sandY++;
                } else
                {
                    cave[sandX, sandY] = 2;
                    sandPlaced++;
                    break;
                }
                if(sandY >= 198)
                {
                    done = true;
                    break;
                }

            }
        }

        Console.WriteLine(sandPlaced);
    }
}