//Codigo para la pagina de registro
$(document).on("ready",function(){
	$("#submitRegister").on("click",function(e){
		e.preventDefault();
		var fName = $("#rName").val();
		var lName = $("#rLName").val();
		var username = $("#rUsername").val();
		var pass = $("#rPassword").val();
		
		var dataToSend = 
    		{
    			"action":"REGISTER",
    			"username" : username,
    			"fName": fName,
    			"lName": lName,
    			"pass"	: pass
    		}; 

    		$.ajax({
			url:"data/applicationLayer.php",
			type:"POST",
			data: dataToSend,
			dataType: "json",
			contentType:"application/x-www-form-urlencoded",
			success: function(jsonO){

				alert("Registration was successful");
				window.location.href='login.html';
			},
			error: function(errorResult){
					alert("Error at registration!");
				}
			}); 
	}); 

	$("#cancelRegister").on("click",function(e){
		e.preventDefault();
		window.location.href='login.html';
	}); 
});
