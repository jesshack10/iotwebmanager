<?php
	header('Accept: application/json');
	header('Content-type: application/json');
	require_once __DIR__ . '/dataLayer.php';
	
	$action = $_POST["action"];

	switch($action)
	{
		case "LOGIN": verifyLogin();
					break;
		case "REGISTER": registerUser();
					break;
		case "LOGOUT": logOut();
					break;
		case "SESSION": getProfile();
					break;
		case "REFRESH": updateData();
					break;
		case "CHANGE_DEV_STATE": changeDevState();
					break;
	}	

//FUNCTION TO UPDATE STATE OF THE DEVICES IN THE DATABASE
function changeDevState(){

	$devName = $_POST["nameDev"];
	$val = $_POST["value"];

	$result = changeDevAction($devName,$val);//Obtiene los valores actuales de los 3 
		//actuadores y el sensor

	if($result["statusText"] == "SUCCESS")
	{
		echo json_encode($result);
	}
	else
	{
		header("HTTP/1.1 406 User not found");
		die('Could not update the value');
	}
}

//UPDATE VALUES IN THE FRONTEND
function updateData(){

	$result = getCurrentValues();//Obtiene los valores actuales de los 3 
		//actuadores y el sensor

	if($result[0]["statusText"] == "SUCCESS")
	{
		echo json_encode($result);
	}
	else
	{
		header("HTTP/1.1 406 User not found");
		die('Could not get values');
	}
}
//VERIFY WHEN A USER LOGIN
	function verifyLogin()
	{
		$username = $_POST["username"];
		$password = $_POST["pass"];


		$result = loginAction($username,$password);


		if($result["statusText"] == "SUCCESS")
		{
			echo json_encode($result);
		}
		else
		{
			header("HTTP/1.1 406 User not found");
			die(json_encode(array('message' => "ERROR",'code' => 1337)));
		}

	}

	function logOut()
	{
		session_start();
		
		if( isset( $_SESSION['username']) ){

		unset( $_SESSION['username'] );
		session_destroy();
		echo json_encode( array('success' => 'Session deleted') );   

		}else{

			die("Session is not set!");
		}
	}

	//GEt profile of the user for Home page
	function getProfile(){
		session_start();
		
		$answer = getProfileData($_SESSION["username"]);

		if (isset($_SESSION["username"]) && $answer["status"] =="SUCCESS")
		{
			echo json_encode($answer);
		}
		else
		{
			header('HTTP/1.1 406 Session has expired, you will be redirected to the login');
			die('Session has expired.');
		}
	}

	function registerUser()
	{
		$name = $_POST["fName"];
		$lname = $_POST["lName"];
		$userName = $_POST["username"];
		$pass = $_POST["pass"];

		$flag = validateUser($userName);
		if($flag["status"] != "SUCCESS")
			$result = registerAction($name,$lname,$userName,$pass);
		else
			die("User already exits");
		if($result["statusText"] == "SUCCESS")
		{
			echo json_encode("SUCCESS");
		}
		else
		{
			header("HTTP/1.1 406 User not found");
			die("User could not be added");
		}
	}
?>
