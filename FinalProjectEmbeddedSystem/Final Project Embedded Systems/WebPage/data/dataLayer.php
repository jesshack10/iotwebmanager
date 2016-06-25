<?php
	
	function connect()
	{
		$servernameDB = "localhost";
		$usernameDB = "root";
		$passwordDB = "";
		$nameDB	= "IOTDB";

		$connection = new mysqli($servernameDB,$usernameDB,$passwordDB,$nameDB);

		if($connection->connect_error)
		{
			return null;
		}else
		{

			return $connection;
		}
	}

	function changeDevAction($actName,$val){
		$conn = connect();
		$sql="UPDATE Actuator SET status='$val' WHERE name='$actName'";

		if($conn!=null)
		{
			if($conn->query($sql)){
				return array("statusText" => "SUCCESS");
			}else{
				return array("statusText" => "FAIL");
			}

		}else{
			return array("statusText" => "FAIL");
		}
	}

	function getCurrentValues(){
		$conn = connect();
		$sqlActuator = "SELECT status FROM Actuator WHERE houseName='myHouse'";///AQUIIIIII
		$sqlSensor = "SELECT readVal FROM Sensor WHERE houseName='myHouse'";////AQUIIIIIIII

		$arrData = array();

		$dataActuator = $conn->query($sqlActuator);
		$dataSensor = $conn->query($sqlSensor);
		if($conn!=null)
		{
			if($dataActuator->num_rows > 0)
			{
				while ($row = $dataActuator->fetch_assoc()) {
					$rowAct = array("rState" => $row["status"],"statusText"=>"SUCCESS");
					array_push($arrData, $rowAct);
				}
			}

			if($dataSensor->num_rows > 0)
			{
				while ($row = $dataSensor->fetch_assoc()) {
					$rowSensor = array("temp" => $row["readVal"],"statusText"=>"SUCCESS");
					array_push($arrData, $rowSensor);
				}
			}
			
			return $arrData;

		}else
		{
			array_push($arrData, array("statusText"=>"FAIL"));
		}
	}

		function registerAction($name,$lname,$userName,$pass)
		{
			$conn = connect();
			if($conn != null)
			{
				$sql = "INSERT INTO Users (fName,lName,username,pass) VALUES ('$name','$lname' ,'$userName','$pass')";

				if ($conn->query($sql)){
						$response = array("statusText" => "SUCCESS");
						return $response;
				} else{
						$response = array("statusText" => "FAIL");
						return $response;
				}
			}
			
		}

		function getProfileData($username)
		{
			$conn = connect();
			if($conn != null)
			{
				$sql = "SELECT * FROM Users WHERE username = '$username'";
				$result = $conn->query($sql);

				if($result->num_rows >0)//ANSWER WAS GOOD!
				{
					while ($row = $result->fetch_assoc()) {
						
							$response = array("fName" => $row["fName"],
										"lName" => $row["lName"],
										"username" => $row["username"],
										"status" => "SUCCESS" );
					}

					return $response;
				}else{

						die("Error getting information about this user");
					}
				}
		}

	//This function is call every time a login is performed
	function loginAction($username,$password)
	{
		$conn = connect();
		if($conn != null)
		{
			$sql = "SELECT fName,username FROM Users WHERE username = '$username' AND pass = '$password'";

			$result = $conn->query($sql);
			
			if($result->num_rows>0)
			{
				while($row = $result->fetch_assoc())
				{
					$response = array("statusText" => "SUCCESS", "fName" => $row["fName"],"username" => $row["username"]);

				 	session_start(); //Session started!
			    	 $_SESSION["username"] = $row["username"];

				}

				return $response;

			}else{
					$response = array("statusText" => "FAIL");
					return $response;
			}
		}else{
					$response = array("statusText" => "FAIL");
					return $response;
			}
	}

	# Query to retrieve a user data
    function validateUser($userName)
    {
        # Open and validate the Database connection
    	$conn = connect();

        if ($conn != null)
        {
        	$sql = "SELECT * FROM Users WHERE userName = '$userName'";
			$result = $conn->query($sql);
			
			# The current user exists
			if ($result->num_rows > 0)
			{
				while($row = $result->fetch_assoc()) 
		    	{
					$conn->close();
					return array("status" => "SUCCESS", "fName" => $row['fName'], "lName" => $row['lName']);
				}
			}
			else
			{
				# The user doesn't exists in the Database
				$conn->close();
				return array("status" => "ERROR");
			}
        }
        else
        {
        	# Connection to Database was not successful
        	$conn->close();
        	return array("status" => "ERROR");
        }
    }
 

?>
