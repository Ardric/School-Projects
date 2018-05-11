# a file that allows for drawing of some flowers via Turtle Graphis

import turtle  

ground = -200


def drawGround():
    turtle.penup()
    turtle.setposition(-500, ground)
    turtle.pendown()
    turtle.setheading(00)
    turtle.color("lightgreen")
    turtle.begin_fill()
    turtle.forward(1000)
    turtle.right(90)
    turtle.forward(300)
    turtle.right(90)
    turtle.forward(1000)
    turtle.right(90)
    turtle.forward(300)
    turtle.end_fill()


def drawSky():
    turtle.penup()
    turtle.setposition(-500, ground)
    turtle.pendown()
    turtle.setheading(00)
    turtle.color("lightblue")
    turtle.begin_fill()
    turtle.forward(1000)
    turtle.left(90)
    turtle.forward(800)
    turtle.left(90)
    turtle.forward(1000)
    turtle.left(90)
    turtle.forward(800)
    turtle.end_fill()


# draws a flower with the x and y coordinate being the lower end
# of the stem.   The size and color of the blossom are as indicat4d.
    
def drawFlower(x=0, y=ground, height=50, size=25, whatcolor="red"):
    turtle.hideturtle()
    turtle.penup()
    turtle.setposition(x, y)
    turtle.pendown()
    turtle.setheading(90)
    turtle.color("darkgreen")
    turtle.forward(height)
    turtle.penup()
    turtle.setposition(x,ground+height/2)
    turtle.setheading(45)
    turtle.pendown()
    turtle.forward(height/3)
    turtle.penup()
    turtle.setposition(x,ground+height/3)
    turtle.setheading(120)
    turtle.pendown()
    turtle.forward(height/4)
    turtle.penup()
    turtle.setposition(x,ground+height)
    turtle.pendown()
    turtle.setheading(0)
    turtle.color(whatcolor)
    turtle.begin_fill()
    turtle.circle(size)
    turtle.end_fill()

