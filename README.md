# Galton Board simulation (in C++)

<p align="center">
  <img width="425" src="https://github.com/nuclearcheesecake/galton-board/blob/master/misc/ellen-qin-fIMqGvVaATk-unsplash.jpg">
</p>

At the end of 2019, after completing my second semester of statistics, I was intrigued by how random processes can generate order, and the seemingly ever-present normal distribution. One afternoon of research on the web brought me to find the Galton Board - a device created by Sir Francis Galton in 1876 that perfectly demonstrates this generation of order. Unable to wait for the shipment of a Board to arrive from across the waters, I decided to code a simulation with varying values to test if the central limit theorem still holds. My results follow below.

# Quick reference to topics needed

* [Combinatorics](https://en.wikipedia.org/wiki/Combinatorics)
* [The Bernoulli and Binomial Distributions](https://en.wikipedia.org/wiki/Binomial_distribution)
* [The Central Limit Theorem](https://en.wikipedia.org/wiki/Central_limit_theorem)

# Theory: The Galton Board and Normal Distribution

As defined by [Wikipedia](https://en.wikipedia.org/wiki/Central_limit_theorem), the **Central Limit Theorem** states that "in some situations, when independent random variables are added, their properly normalized sum tends toward a normal distribution (informally a _bell curve_) even if the original variables themselves are not normally distributed".

The Galton Board contains hundreds of tiny spheres, which in turn cascade down sevaral layers of pegs (arranged in a triangle) and end up in one of several bins. The reason this contraption is noteworthy is because the shape of the resulting collection of spheres, as a whole, almost always results in the bell curve.

To understand this, we will consider each sphere separately as the subject of its own statistical trial. If we consider **n levels** (or layers) of pegs, it means that each trial will consist out of n binary **choices**, where each choice is to go either left or right when it reaches a peg. A sphere can only reach one peg per level, but which side it "chooses" to fall down will influence in which bin the sphere ends up in. For example, if it consistently falls down the right-side of each peg it encounters, it will end up in the bin the furthest to the right. The probability on each choice at a peg is equal (p = 0,5) and it is the same on each level. We can use Pascal's triangle to visualise its path mathematically:

<p align="center">
  <img width="425" src="https://github.com/nuclearcheesecake/galton-board/blob/master/misc/588px-Pascal_triangle.png">
</p>
(source: https://commons.wikimedia.org/wiki/File:Pascal_triangle.svg)

Above, the values describe the number of paths towards a single peg, and in the final level, to a single **bin** (the final resting place of a single ball). Therefore it is more likely to land in the bin with 252 possible paths leading to it, than it is to land in the outer bins, where the path consists of either all choices equalling "left" or all equalling "right".
See: [Galton Board and Pascal's Triangle](https://www.youtube.com/watch?v=mzbAVFIs7sE)

This gives an intuitive understanding of why there are more spheres "heaping up" in the middle, creating the normal distribution. But in a mathematical sense we can say the following: The probability distribution that describes the "choices" that each ball makes, is called the **Binomial distribution** (which depends the number of successes for a number of trials). For this to make sense, we need to consider each "right" to be a success and each left a fail (thus each peg is a **Bernoulli Trial**), then the entire path down can be described in how many successes the sphere made (or mapping how many times it went right).

<p align="center">
  <img width="225" src="https://github.com/nuclearcheesecake/galton-board/blob/master/misc/Galton_board.png">
</p>
(source: https://commons.wikimedia.org/wiki/File:Galton_Box.svg)

Now that we grasp each binomial trial on its own, landing each sphere in a single bin, we come to the big paradigm shift: considering all X trials, be it 500 or 1 000 000! It is in this step where the normal distribution appears, when we consider all X independent trials - even though individually the paths are binomially distributed, after X trials, the curve the spheres take on will approximate a Normal curve. And according to the CLT, the more spheres we use (and thus the more trials we add), the more "normal" it will become. That is demonstrated below, using the _totalNumOfTests_ variable. In the practical, you can change the value of this variable, as well as the value of the _X_ variable, where the number of levels can be increased, to see how it affects the shape of the curve.

They kay takeaway is that, whcih a large number of trials, the ultimate bin where a sphere ends up in becomes more likely to be closer to the centre, since it has more paths, creating a normal curve.

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

# Running the code

### Installing the program:

You can navigate to the "galton.cpp" file and download it directly from GitHub, or type the following in your terminal:

```shell
    git clone https://github.com/nuclearcheesecake/galton-board
```

to copy the file into whichever directory you want the program.

### Running the code
  
If you are running the code in a UNIX environment, you first have to compile the program manually. Navigate to the directory where you downloaded the file and enter:

```shell
    g++ galton.cpp
```

There now exists a file containing the machine code named "a.out". Run the program by entering:

```shell
    ./a.out
```

Alternatively you, and users outside of UNIX, can run it from any IDE that supports the C++ language.

### Example

<p align="center">
  <img width="425" src="https://github.com/nuclearcheesecake/galton-board/blob/master/misc/galtonsim.png">
</p>
