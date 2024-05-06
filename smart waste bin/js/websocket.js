var binLevel = 0;
var binImage = document.getElementById("binImage");
var websock;
var longitude;
var lattitude;









function Location(){
  window.open("https://www.google.com/maps/search/?api=1&query=" + lattitude + "%2C" + longitude,
  "", "width=300, height=300");
}

var read_key = "59ZDOL4E0A93JDJE";
var device_id = "2429905";

$(document).ready(function ()
{
    GetData();

 
});

function GetData()
{
    var url = 'https://api.thingspeak.com/channels/' + device_id + '/feeds.json?api_key=' + read_key + '&results=2';
    $.ajax
    ({
        url: url,
        type: 'GET',
        contentType: "application/json",
        //dataType: "json",
        //crossDomain: true,
        success: function (data, textStatus, xhr) {
            $.each(data, function (i, item) {
                if (i == 'feeds') {
                    var ubound = item.length;
                 $('#txtField1').val(item[ubound - 1].field1);
               $('#txtField2').val(item[ubound - 1].field2);
              $('#txtField3').val(item[ubound - 1].field3);
              
                  binLevel = (item[ubound - 1].field1);
                lattitude= (item[ubound - 1].field2);
                 longitude = (item[ubound - 1].field3);
                
                  document.getElementById("status").style.color ="white";
                  document.getElementById("bin_id").innerText = "SWB - 001";
                }
              });
            },
            error: function (xhr, textStatus, errorThrown) {
                alert(errorThrown);
            }
        });

        setTimeout(GetData, 1000);

    
    }




    setInterval(()=>{
      gauge1.update(binLevel);
    
      if(binLevel <= 25){
      binImage.src = "image/black.png"
      }
      else if(binLevel > 25 && binLevel <= 50){
        binImage.src = "image/red.png"  
      }
       
      else if(binLevel > 50 && binLevel <= 75){
        binImage.src = "image/yellow.png"  
      }
       
      else if(binLevel > 75){
        binImage.src = "image/green.png"  
      }
  
        },1000);
    
    

// *********************** BATTERY ANIMATION SETUP********************************
var config1 = liquidFillGaugeDefaultSettings();   
// *****************************************************************************
// const ctx = document.getElementById('myChart').getContext('2d');


config1.circleColor = "rgba(0, 45,150, 0.842)";
      config1.textColor =  "rgba(0, 45,150, 0.842)";
      config1.waveColor =  "rgba(0, 45,150, 0.842)";
      config1.waveTextColor = "white";
var gauge1 = loadLiquidFillGauge("fillgauge1",0,config1);

























// function connect() {

//   websock = new WebSocket("ws://192.168.4.1/ws");
// }
// //connect();
// websock = new WebSocket("ws://192.168.4.1/ws");



// websock.addEventListener('onload',()=>{
// // location.reload();
// });

// var i  = 0;

// websock.onmessage = function(event) {
//       // console.log(event);
//     data = event.data;

//       // document.getElementById('message').innerText = (event.data);
// receive = JSON.parse(event.data);
// console.log(receive);
// // temp.setValueAnimated(receive.temp, 1);
// document.getElementById("bin_id").innerText = receive.BIN_ID;
// binLevel = receive.WASTE_LEVEL;    //Math.floor(Math.random() * 100);
// longitude = receive.LONGITUDE;
// latitude = receive.LATITUDE;

// };



// websock.onopen = function(event1) {
// console.log("WebSocket is open now.");
// // ed1.style.background = "#00e600";

//  //speak("device is conntected");
//  //alert("yes connect");
// //  conn.innerHTML = "Connected";
// document.getElementById("status").style.color ="white";

// }

// websock.onerror = function(evt) {
//   //speak("device is disconnected");
// console.log("WebSocket is closed now.");
// // conn.innerHTML = "Error in connection";

// // conn.style="color:red;font-size:80%;margin-left:5%";

// document.getElementById("status").style.color="#e61511e8";
// //  conn.style="color:rgb(200,50,50);font-weight:bold;text-align:left;";
// // connect();
// }

// websock.onclose = function(evt) {
//  // speak("device is disconnected");
//   console.log("WebSocket is closed now.");
//   // conn.innerHTML = "Connection Closed";
//   document.getElementById("status").style.color="#e61511e8";
//   // conn.style="color:red;font-size:80%;margin-left:5%";
  
// }
 



