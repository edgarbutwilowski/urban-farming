const httpService = require("http");
const url = require("url");
const validator = require("validator");

let moisture = 0.0;
let time = "";

const hostAddress = "0.0.0.0";
const portNo = 8000;

const requListen = (requ, resp) => {
  const urlObj = url.parse(requ.url, true).query;
  if(urlObj.moisture && urlObj.time) {
    moisture = validator.escape(urlObj.moisture);
    time = new Date().toISOString().slice(0, 10);
    resp.writeHead(200);
    resp.end();
  } else {
    resp.writeHead(200);
    let html = "<html><head>\r\n";
    html += "<script src=\"https://cdn.jsdelivr.net/npm/chart.js@3.7.0/dist/chart.min.js\"></script>\r\n"
    html += "</head><body>\r\n";
    html += "<h1>Urban Farming Project</h1>\r\n";
    html += "<p>Moisture: " + moisture + " %; Last Transmission Time: " + time + "</p>\r\n";
    html += "<div style=\"width: 50%;\">\r\n";
    html += "<canvas id=\"gardenChart\"></canvas>\r\n";
    html += "</div>\r\n";
    html += "<script>\r\n";
    html += "const ctx = document.getElementById('gardenChart').getContext('2d');\r\n";
    html += "const gardenChart = new Chart(ctx, {\r\n";
    html += "type: 'doughnut',\r\n";
    html += "data: {\r\n";
    html += "  labels: ['dry', 'wet'],\r\n";
    html += "   datasets: [{\r\n";
    html += "        label: 'Moisture',\r\n";
    html += "        data: [" + (100.0 - moisture) + ", " + moisture + "],\r\n";
    html += "       backgroundColor: [\r\n";
    html += "            'rgba(255, 99, 132, 0.2)',\r\n";
    html += "            'rgba(75, 192, 192, 0.2)',\r\n";
    html += "        ],\r\n";
    html += "        borderColor: [\r\n";
    html += "            'rgba(255, 99, 132, 1)',\r\n";
    html += "           'rgba(75, 192, 192, 1)',\r\n";
    html += "        ],\r\n";
    html += "        borderWidth: 1\r\n";
    html += "    }]\r\n";
    html += " },\r\n";
    html += "options: {\r\n";
    html += "}\r\n";
    html += "});\r\n";
    html += "</script></body>\r\n";
    resp.end(html);
  }
};

const myServer = httpService.createServer(requListen);
myServer.listen(portNo, hostAddress, () => { console.log("Server running"); });
