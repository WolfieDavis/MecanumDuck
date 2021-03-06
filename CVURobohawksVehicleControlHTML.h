R"====(

<html>

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0" />

    <style>
        body {
            overflow: hidden;
            padding: 0;
            margin: 0;
            background-color: #BBB;
            font-size: 14pt;
            font-family: Arial;
        }

        #title {
            position: absolute;
            /* top: 8px; */
            width: 100%;
            /* padding-top: 10px; */
            text-align: center;
            font-size: 18pt;
        }

        #info {
            position: absolute;
            top: 70px;
            width: 100%;
            /* padding: 5px; */
            text-align: center;
        }


        #joy-container {
            position: absolute;
            width: 300;
            top: 150px;
            left: calc(100vw*1/5);
            height: calc(100vh - 200px);
            overflow: hidden;
            padding: 0;
            margin: 0;
            -webkit-user-select: none;
            -moz-user-select: none;
            border: solid 2px red;

        }

        #joy-container2 {
            position: absolute;
            width: 300;
            top: 150px;
            left: calc(100vw*3/5);
            height: calc(100vh - 200px);
            overflow: hidden;
            padding: 0;
            margin: 0;
            -webkit-user-select: none;
            -moz-user-select: none;
            border: solid 2px red;
        }

        #wheel-adjust {
            position: absolute;
            bottom: 0px;
            width: 100%;
            padding: 5px;
            text-align: center;
        }

        button#run-autonomous {
            border: solid grey 1px;
            background-color: red;
            cursor: pointer;
            transition: 0.2s ease-in-out;
            font-size: 14pt;
        }

        button#run-autonomous:hover {
            box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2);
        }

        span#autonomous-progress {
            color: grey;
            font-weight: bold;
        }
    </style>

</head>

<body>
    <h3 id="title">Mecanum Duck!</h3>
    <div id="joy-containers">
        <div id="joy-container"></div>
        <div id="joy-container2"></div>
    </div>

    <div id="info">
        <!-- <span id="button">
            <button id="run-autonomous" onclick="runAutonomous()">Run autonomous</button>
            <span id="autonomous-progress" style="display:none">Running autonomous...</span>
        </span>
        </br> -->
        <!-- <span id="touch-message">or Touch the screen to move</span>
        <br /> -->
        <span id="result"></span>
        <br />
        <span id="inputs"></span>
        <br />
        <span id="wheels"></span>

    </div>

    <!-- <div id="wheel-adjust">
        <a href="./CVURobohawksVehicleWheelTuneHTML.html" id="wheel-adjust-link">Adjust wheel error</a>
    </div> -->
    <script src="./CVURobohawksVehicleJoyStickJS.js"></script>
    <script>
        console.log("touchscreen is", VirtualJoystick.touchScreenAvailable() ? "available" : "not available");

        const messageA = 'or Touch the screen to move';
        const messageB = 'Touch screen disabled';

        console.log(navigator.getGamepads());


        var joystick = new VirtualJoystick({
            container: document.getElementById('joy-container'),
            mouseSupport: true,
            limitStickTravel: true,
            stationaryBase: true,
            centerBase: true,
            sprungStick: false,
            baseOutlineColor: 'black',
            baseCenterColor: 'black',
            stickColor: "rgba(255, 0, 0, 0.75)",

        });

        var joystick2 = new VirtualJoystick({
            container: document.getElementById('joy-container2'),
            mouseSupport: true,
            limitStickTravel: true,
            stationaryBase: true,
            centerBase: true,
            sprungStick: false,
            baseOutlineColor: 'black',
            baseCenterColor: 'black',
            stickColor: "rgba(255, 0, 0, 0.75)",

        });


        joystick.addEventListener('touchStart', function () {
            console.log('down')
        })
        joystick.addEventListener('touchEnd', function () {
            console.log('up')
        })

        // var prevX = 0;
        // var prevY = 0;
        var newX = 0;
        var newY = 0;

        // var prevX2 = 0;
        // var prevY2 = 0;
        var newX2 = 0;
        var newY2 = 0;


        setInterval(function () {
            const myGamepad = navigator.getGamepads()[0];

            var outputEl = document.getElementById('result');
            var inputsEl = document.getElementById('inputs');

            // newX = Math.round(joystick.deltaX());
            // newY = Math.round(joystick.deltaY()) * -1;
            // newX2 = Math.round(joystick2.deltaX());
            // newY2 = Math.round(joystick2.deltaY()) * -1;

            joystick._onDownIncremental();
            // joystick._onMove(x,y);
            joystick._onMoveIncremental(Math.round(myGamepad.axes[0] * 100), Math.round(myGamepad.axes[1] * 100));
            joystick._onUp();

            joystick2._onDownIncremental();
            // joystick2._onMove(x,y);
            joystick2._onMoveIncremental(Math.round(myGamepad.axes[2] * 100), Math.round(myGamepad.axes[3] * 100));
            joystick2._onUp();

            outputEl.innerHTML = '<b>Position:</b> '
                + ' Lx: ' + newX
                + ' Ly: ' + newY
                + ' Rx: ' + newX2
                + ' Ry: ' + newY2;

            inputsEl.innerHTML = '<b>Inputs:</b> '
                + ' Lx: ' + Math.round(myGamepad.axes[0] * 100)
                + ' Ly: ' + Math.round(myGamepad.axes[1] * 100)
                + ' Rx: ' + Math.round(myGamepad.axes[2] * 100)
                + ' Ry: ' + Math.round(myGamepad.axes[3] * 100);

            // if (newX != prevX || newY != prevY) {
            //     var xhr = new XMLHttpRequest();
            //     xhr.open('PUT', "./jsData.html?x=" + newX + "&y=" + newY)
            //     xhr.send();
            // }
            // prevX = newX;
            // prevY = newY;
            // prevX2 = newX2;
            // prevY2 = newY2;

        }, 1 / 10 * 1000);






        var mLF;
        var mLB;
        var mRF;
        var mRB;

        var mLFprev;
        var mLBprev;
        var mRFprev;
        var mRBprev;

        setInterval(function () {
            const myGamepad = navigator.getGamepads()[0];
            var leftX = myGamepad.axes[0];
            var rightX = myGamepad.axes[2];
            var rightY = myGamepad.axes[3];

            var maxPower = 1;


            if (Math.abs(leftX) > .1 || Math.abs(rightX) > .1 || Math.abs(rightY) > .1) {
                drive(maxPower, rateCurve(-rightY, 1.7), rateCurve(-leftX, 1.7) * 0.7 / 0.9, rateCurve(rightX, 1.7));
            } else {
                drive(0, 0, 0, 0);
            }

            document.getElementById('wheels').innerHTML = '<b>Wheels:</b> '
                + ' mLF: ' + Math.round(mLF * 100)
                + ' mLB: ' + Math.round(mLB * 100)
                + ' mRF: ' + Math.round(mRF * 100)
                + ' mRB: ' + Math.round(mRB * 100);

            if (mLF != mLFprev || mLB != mLBprev || mRF != mRFprev || mRB != mRBprev) {
                var xhr = new XMLHttpRequest();
                xhr.open('PUT', "./jsData.html?mLF=" + mLF + "&mLB=" + mLB + "&mRF=" + mRF + "&mRB=" + mRB)
                xhr.send();
            }

            mLFprev = mLF;
            mLBprev = mLB;
            mRFprev = mRF;    
            mRBprev = mRB;

        }, 100);

        function drive(power, forward, yaw, strafe) {
            Forward = forward * power;
            Yaw = yaw * power;
            Strafe = strafe * power;

            mRF = (Forward + Yaw - Strafe);
            mLF = (Forward - Yaw + Strafe);
            mRB = (Forward + Yaw + Strafe);
            mLB = (Forward - Yaw - Strafe);

            return (mRF, mLF, mRB, mLB);
        }

        function rateCurve(input, rate) {
            return Math.pow(Math.abs(input), rate) * ((input > 0) ? 1 : -1);
        }









        function setDisplay(id, display) {
            document.getElementById(id).style.display = display;
        }

        function runAutonomous() {
            setDisplay('run-autonomous', 'none');
            setDisplay('autonomous-progress', 'inline');

            document.getElementById('joy-container').style.zIndex = -100;
            document.getElementById('touch-message').innerHTML = messageB;

            var xhr = new XMLHttpRequest();

            xhr.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    setDisplay('run-autonomous', 'inline');
                    setDisplay('autonomous-progress', 'none');

                    document.getElementById('touch-message').innerHTML = messageA;
                    document.getElementById('joy-container').style.zIndex = '';
                }
            }
            xhr.open('GET', '/runAutonomous');
            xhr.send();
        }

        
    </script>
</body>

</html>

)===="