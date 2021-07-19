# galton-board

At the end of 2019, after completing my second semester of statistics, I was intrigued by how random processes can generate order, and the seemingly ever-present normal distribution. One afternoon of research on the web brought me to find the Galton Board - a device created by Sir Francis Galton in 1876 that perfectly demonstrates this generation of order. Unable to wait for the shipment of a Board to arrive from across the waters, I decided to code a simulation with varying values to test if the central limit theorem still holds. My results follow below.



The Galton Board is a contraption invented by Sir Francis Galton in 1876 to demonstrate the central limit theorem. The device uses pegs and cascading balls to show how randomness in nature can still result in a Normal Distrubution.

For an explanation of the code, and the statistics behind it, visit: https://nuclearcheesecake.github.io/galton/

# Quick reference to topics needed

* <span style="font-family:Courier; font-size:18pt;"> [Combinatorics](https://en.wikipedia.org/wiki/Combinatorics)</span>
* <span style="font-family:Courier; font-size:18pt;"> [The Bernoulli and Binomial Distributions](https://en.wikipedia.org/wiki/Binomial_distribution)</span>
* <span style="font-family:Courier; font-size:18pt;"> [The Central Limit Theorem](https://en.wikipedia.org/wiki/Central_limit_theorem)</span>

# Theory: The Galton Board and Normal Distribution

<span style="font-family:Courier; font-size:18pt;">As defined by [Wikipedia](https://en.wikipedia.org/wiki/Central_limit_theorem), the **Central Limit Theorem** states that "in some situations, when independent random variables are added, their properly normalized sum tends toward a normal distribution (informally a _bell curve_) even if the original variables themselves are not normally distributed".</span>

<span style="font-family:Courier; font-size:18pt;">The Galton Board contains hundreds of tiny spheres, and we will consider each separately as the subject of its own statistical trial. If we consider 11 **levels** (or layers) of pegs, it means that each trial will consist out of 11 binary **choices**, to go either left or right when it reaches a peg. The probability on each choice is equal (p = 0,5) and it is the same on each level. We can use Pascal's triangle to visualise its path mathematically:</span>

![alt text](/images/pascal.png)
(source: https://commons.wikimedia.org/wiki/File:Pascal_triangle.svg)

<span style="font-family:Courier; font-size:18pt;">Above, the values describe the number of paths towards a single peg, and in the final level, to a single **bin** (the final resting place of a single ball). Therefore it is more likely to land in the bin with 252 possible paths leading to it, than it is to land in the outer bins, where the path consists of either all choices equalling "left" or all equalling "right". Even in the simulation, when the number of levels increases, and as it becomes more unlikely for the spheres to fall in the outer bins, they almost always remain empty!
See: [Galton Board and Pascal's Triangle](https://www.youtube.com/watch?v=mzbAVFIs7sE)</span>

<span style="font-family:Courier; font-size:18pt;">This gives an intuitive understanding of why there are more spheres "heaping up" in the middle, creating the normal distribution. But in a mathematical sense we can say the following:
The probability distribution that describes the "choices" that each ball makes, is called the **Binomial distribution**. If we consider each "right" to be a success and each left a fail (thus each peg is a **Bernoulli Trial**), the entire path down can be described in how many successes the sphere made (or mapping how many times it went right).</span>

<span style="font-family:Courier; font-size:18pt;">Now that we grasp each binomial trial on its own, landing each sphere in a single bin, we come to the big paradigm shift: considering all X trials, be it 500 or 1 000 000! It is in this step where the normal distribution appears, when we consider all X independent trials: Even though individually the paths are binomially distributed, after X trials, the curve the spheres take on will approximate a Normal curve. And according to the CLT, the more balls we use (and thus the more trials we add), the more "normal" it will become. That is demonstrated below, using the _totalNumOfTests_ variable.</span>

<span style="font-family:Courier; font-size:18pt;">A second expansion is that of the _X_ variable, where the number of levels can be increased.</span>

# Practical: The C++ simulation

The code for the simulation was developed using this idea that each trial yields a number of successes (from 0 to X). But first we must "build" our board, and populate it with spheres:

```cpp
int X;
int totalObtained[X]; // each row represents the total number of turns made (0 = left, 1 = right) from 0 rights to X rights
int tempTotal, totalNumOfTests;

cout << "\t\tGALTON BOARD: A simulation\n";
cout << "\t\t===========================\n\n";
cout << "Please enter the number of levels to include in the experiment: "; // recommended is 12
cin >> X;
cout << "Please enter a number of balls to include in the experiment: "; // recommended is 500 - 1000
cin >> totalNumOfTests;

for (int k = 0; k < X; k++)
{
  totalObtained[k] = 0;
}
```

Let's first discuss the **variables:**
* _X_: The number of levels
* _totalObtained[X]_: An array storing the total number of balls in each bin
* _tempTotal_: The total for each trial - incremented as the sphere "makes a choice"
* _totalNumOfTests_: The total number of spheres

Next the user can define how many levels and spheres to include in the simulation. Now that we have fixed the number of levels, we can define the size of the array representing the bins, and initialise it with 0 (as all bins are still empty).

As a single sphere traverses the levels, it makes a total number of decisions, which are accumulated in the _tempTotal_ variable for each sphere, where 0 = left and 1 = right. After the ball traverses every level and reaches the end, the respective element of the total-obtained-array is incremented with one as a sphere lands in a specific bin.

Here is the heart of decision-making in the code, a random decision of either **0** or **1**:

```cpp
srand(time(0));

for (int m = 0; m < totalNumOfTests; m++)
{
    // results of a single trial (ie a single ball)
    tempTotal = 0;

    for (int k = 0; k < X; k++) // X layers of decisions to traverse, either goes left(0) or right(1)
    {
        int turn = rand() % 2;
        tempTotal += turn;
    }
      totalObtained[tempTotal]++; // the total number of rights it made is the index of where it lands
  }
```

And after all spheres have been settled into a bin, the results are displayed using a simple for-loop:

```cpp
cout << "\n\n\tResults\n"; // displaying the simulation of the galton board
cout << "-------------------------\n\n";

for (int k = 0; k < X; k++)
{
    for (int r = 0; r < totalObtained[k]; r++)
    {
        cout << "X";
    }
    cout << endl;
}
```
# Example

Thus if we choose the number of levels to be 12, and the number of balls as 500, the program might display the following:

![alt text](/images/galtonsim.png)

### Installing the program:

You can navigate to the "galton.cpp" file and download it directly from GitHub, or type the following in your terminal:

```shell
    git clone https://github.com/nuclearcheesecake/galton-board
```

to copy the file into whichever directory you want the program.

### Running the code
  
As usual with C++ programs in UNIX, you first have to compile the program manually. Navigate to the directory where you downloaded the file and enter:

```shell
    g++ galton.cpp
```

There now exists a file containing the machine code named "a.out". Run the program by entering:

```shell
    ./a.out
```

Alternatively (and users outside of UNIX) you can run it from any IDE that supports the C++ language.

### Example
  
  
<img src="https://github.com/nuclearcheesecake/galton-board/blob/master/galtonsim.png" class="center">
