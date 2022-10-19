import sys
import csv
from tkinter import Y
sys.argv[1]
import matplotlib.pyplot as plt
import numpy as np
from numpy.linalg import inv

points = []
x = []
y = []
def createPlot(filepath):
  
  with open(filepath, newline = '') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
      points.append(row)

    for p in points:
      x.append(int(p.get("year")))
      y.append(int(p.get("days")))
    plt.plot(x,y)
    # naming the x axis
    plt.xlabel('Year')
    # naming the y axis
    plt.ylabel('Number of Frozen Days')
  
    # giving a title to my graph
    plt.title('Graph of Frozen Day Trends: Lake Mendota')
    plt.xlim([1855, 2020])
    plt.ylim([0, 175])
    # function to show the plot
    #plt.locator_params(nbins = 10)
    plt.savefig("plot.jpg")

    #plt.show()
  
  return

def Q3a():
  rows = len(points)
  cols = 2
  xmat = [[0 for _ in range(cols)] for _ in range(rows)]

  for i in range(0, rows):
    xmat[i][0] = 1
    xmat[i][1] = x[i]
  
  return np.array(xmat)

def Q3b():
  rows = len(points)
  yVec = [0 for _ in range(rows)]

  for i in range(0, rows):
    yVec[i] = y[i]
  
  return np.array(yVec)

def Q3c():
  X = Q3a()
  XT = X.transpose()

  return np.matmul(XT, X)

def Q3d():
  return inv(Q3c())

def Q3e():
  X = Q3a()
  XT = X.transpose()
  return np.matmul(Q3d(),XT)

def Q3f():
  X = Q3e()
  return X.dot(Q3b())

def Q4():
  b_hat = Q3f()
  intercept = b_hat[0]
  slope = b_hat[1]
  xtest = 2021

  return intercept + (slope*xtest)

def Q5():
  b_hat = Q3f()
  if b_hat[1] == 0:
    print("Q5a: =")
    print("Q5b:The number of ice days for Lake Mendota will remain around the same as previous years.")
  elif b_hat[1] > 0:
    print("Q5a: >")
    print("Q5b: The number of ice days for Lake Mendota will increase.")
  else:
    print("Q5a: <")
    print("Q5b: The number of ice days for Lake Mendota will decrease.")

def Q6():
  b_hat = Q3f()
  intercept = b_hat[0]
  slope = b_hat[1]
  year = 0 - intercept
  year = year/slope
  print("Q6a: " + str(year))
  print("Q6b: This is not a compelling prediction based on the trends in the data because it does not account for factors that may impact the climate in the coming years. With the ongoing climate crisis it is likely that the year in which there are no more ice days on Lake Mendota will come sooner.")

if __name__ == "__main__":
  createPlot(sys.argv[1])
  print("Q3a:")
  print(Q3a())
  print("Q3b:")
  print(Q3b())
  print("Q3c:")
  print(Q3c())
  print("Q3d:")
  print(Q3d())
  print("Q3e:")
  print(Q3e())
  print("Q3f:")
  print(Q3f())
  print("Q4: " + str(Q4()))
  Q5()
  Q6()
