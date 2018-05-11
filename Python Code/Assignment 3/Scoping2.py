# This program is a silly demo used to deal with scope in a lab
# written by Scott McElfresh


# -----------
def f(a):
    a = 10
    x
    print("in f: ")
    print("   x = ", x)
    print("   a = ", a)

# -----------
def g(x, z):
    x = 'hello'
    y = 50
    z = [1,2,3]
    print("in g: ")
    print("   x = ", x)
    print("   y = ", y)
    print("   z = ", z)
    f(x)
    print("in g: ")
    print("   x = ", x)
    print("   y = ", y)
    print("   z = ", z)
    f(y)
    print("in g: ")
    print("   x = ", x)
    print("   y = ", y)
    print("   z = ", z)


# ------------
def main():
    global x
    x = 1
    global y
    y = 2
    a = 5
    f(x)
    g(x,y)

    print("in main: ")
    print("   x = ", x)
    print("   y = ", y)
    print("   a = ", a)
    
#############################
main()
