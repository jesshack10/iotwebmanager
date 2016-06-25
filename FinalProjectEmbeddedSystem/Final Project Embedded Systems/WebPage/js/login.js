//Codigo para la pagina login
$(document).on("ready",function(){


	$("#submitLogin").on("click",function(e){
		e.preventDefault();
		var username = $("#username").val();
		var password = $("#password").val();
		
		var dataToSend = 
    		{
    			"action":"LOGIN",
    			"username" : username,
    			"pass"	: password
    		}; 

    		$.ajax({
			url:"data/applicationLayer.php",
			type:"POST",
			data: dataToSend,
			dataType: "json",
			contentType:"application/x-www-form-urlencoded",
			success: function(jsonO){

				alert("Hi " + jsonO.username);
				redirectHome();
			},
			error: function(errorResult){
				alert("Could not login");
				}
			}); 
	}); 
});

function redirectHome(){
		window.location.href = 'home.html';
};
