from flask import Flask, render_template
import random

app = Flask(__name__)

images = [
        "http://worldartsme.com/images/numbers-circle-graphic-clipart-1.jpg",
        "http://suburban-poverty.com/wp-content/uploads/2015/06/numeral-2.jpg",
        "https://static1.squarespace.com/static/57201fbd8a65e2a461613e05/t/5a5d270f4192027c06727faf/1516054292266/3.jpg",
        "https://thumbs.dreamstime.com/b/3d-golden-number-4-3300959.jpg",
        "http://www.kidsmathgamesonline.com/images/pictures/numbers600/number5.jpg",
        "http://www.kidsmathgamesonline.com/images/pictures/numbers600/number6.jpg",
        "http://numerologystars.com/wp-content/uploads/2012/09/number-7.jpg",
        "https://previews.123rf.com/images/asmati/asmati1703/asmati170300716/72981955-number-8-sign-design-template-element-vector-white-icon-in-bluish-circle-on-white-background-isolate.jpg",
        "https://i.ytimg.com/vi/JTvJ-M-JeMs/maxresdefault.jpg"
        ]

@app.route('/')
def index():
    url = random.choice(images)
    return render_template('index.html', url=url)

if __name__ == "__main__":
    app.run(host="0.0.0.0")
