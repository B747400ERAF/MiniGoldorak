function httpGet(url) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", url, false);
    xmlHttp.send(null);
    return xmlHttp.responseText;
}

function sendServoPos(input) {
    httpGet('get?servo=' + input.value);
}

var slider = document.getElementById("myRange");
var output = document.getElementById("value");

output.innerHTML = slider.value;

slider.oninput = fonction() {
    output.innerHTML = this.value;
}