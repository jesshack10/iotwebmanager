//Home page
var ctrlProfileAppend = false;
var refreshTime = 2000;	//Time in milliseconds to refresh data

$(document).on('ready',function(){

	function refreshData(){
		//Code to set up the information in the profile Tab
	var dataToSend = 
            		{
            			"action":"REFRESH"
            		}; 
		$.ajax({
		url:"data/applicationLayer.php",
		data:dataToSend,
		type:"POST",
		dataType: "json",
		contentType:"application/x-www-form-urlencoded",
		success: function(jsonData){	
			//alert(jsonData[0]+jsonData[1]+jsonData[2]+jsonData[3]);

			if(jsonData[0].rState==0){
				$("#btnRoom1").attr("value", "OFF");
				$("#focoImg1").attr("src","img/foco.jpg");
			}else{
				$("#btnRoom1").attr("value", "ON");
				$("#focoImg1").attr("src","img/foco.gif");
			}

			if(jsonData[1].rState==0){
				$("#btnRoom2").attr("value", "OFF");
				$("#focoImg2").attr("src","img/foco.jpg");
			}else{
				$("#btnRoom2").attr("value", "ON");
				$("#focoImg2").attr("src","img/foco.gif");
			}

			if(jsonData[2].rState==0){
				$("#btnRoom3").attr("value", "OFF");
				$("#focoImg3").attr("src","img/foco.jpg");
			}else{
				$("#btnRoom3").attr("value", "ON");
				$("#focoImg3").attr("src","img/foco.gif");
			}


			$("#tempValue").html(jsonData[3].temp + "ºC");

			var setPoint = $("#setPoint").val();
			if(jsonData[3].temp >= setPoint){
				$("#sensorImg").attr("src","img/temp.gif");
			}
			else{
				$("#sensorImg").attr("src","img/temp.png");
			}
		},
		error: function(errorResult){
			console.log("JsonDataError", "Error loading user data");
			}
		});  
	}
	//Call the function each two seconds
	setInterval(refreshData,refreshTime);

	//Code to set up the information in the profile Tab
	var dataToSend = 
            		{
            			"action":"SESSION"
            		}; 
		$.ajax({
		url:"data/applicationLayer.php",
		data:dataToSend,
		type:"POST",
		dataType: "json",
		contentType:"application/x-www-form-urlencoded",
		success: function(jsonData){

				var userHTMLdata="";

				userHTMLdata += "<h3>Username: " + jsonData.username + "</h3>";
				userHTMLdata += "<h3>FirstName: " + jsonData.fName + "</h3>";

				userHTMLdata += "<h3>LastName: " + jsonData.lName + "</h3>";



				(ctrlProfileAppend==false) ? $("#content-profile").append(userHTMLdata) : ctrlProfileAppend=true;
				ctrlProfileAppend=true;

				//To show the username at the upper label
				$("#userHeader").html("Welcome " + jsonData.username +" !");

		},
		error: function(errorResult){
			console.log("JsonDataError", "Error loading user data");
			}
		});  

		$("#content-home").hide();


	  //CALL WHEN A COMMAND FTO TURN ON/OFF IS REQUESTED
        $("#devicesTable").on("click",".button",function(){
        	var nameDev=$(this).parent().parent().find("td").find("b").html();
        	var value = $(this).attr("value");
        	var currentButton = $(this);
        	value = (value=="OFF")?1:0;

        	alert(nameDev);
        	alert(value);

        	var dataToSend ={
        		"action":"CHANGE_DEV_STATE",
        		"nameDev": nameDev,
        		"value": value 
        	};
        	
        	$.ajax({
        		url:"data/applicationLayer.php",
        		type:"POST",
        		data:dataToSend,
        		dataType:"json",
        		contentType:"application/x-www-form-urlencoded",
        		success:function(){
        			console.log("success to turn on/off your device");
        			$(currentButton).attr("value",value);
        		},
        		error: function(){
        			console.log("Request Error","It was impossible to sent the request");
        		}
        	});

        });

});

//This function recieves the tabName paramenter
//and it shows the clicked Tab ans hide the others
//in the Home Page
function showCurrentTab(tabName){
	$("#content-home").hide();
	$("#content-devices").hide();
	$("#content-addUser").hide();
	$("#content-profile").hide();
	$("#content-logout").hide();

	switch(tabName){
		case "home": $("#content-home").show();
					 $("#addHouseTable").hide();
				break;
		case "devices": $("#content-devices").show();
						$("#addDeviceTable").hide();
						$("#addDevBoxButton").hide();
				break;
		case "addUser": $("#content-addUser").show();
						$("#devLinkTable").hide();
				break;
		case "profile": $("#content-profile").show();
				break;
		case "logout": //Call function to Logout Session!
						requestLogout();
				break;
	}
}

function requestLogout()
{
	var dataToSend = {
		"action":"LOGOUT"
	}

	$.ajax({
		url:"data/applicationLayer.php",
		data:dataToSend,
		type:"POST",
		dataType: "json",
		contentType:"application/x-www-form-urlencoded",
		success:function(){
			alert("GoodBye!,we hope to see you again!");
		},
		error:function(){
			console.log("LOGOUT error","Session was not correctly terminated!");
		}
	});

	window.location.href = "login.html";
}

function addDevices(){
	$("#addDeviceTable").show();
	$("#addDevBoxButton").show();
}
function updateImage(){
	var image = "img/"+$("#listImages").val();
	$("#imgOfDev").attr('src',image);
}