from flask import Flask, g

app = Flask(__name__)
app.debug = True

app.config.from_object(__name__)
app.config.update(dict(


      ))      

@app.route("/")
def hangman():
  return render_template("hangman.html")
