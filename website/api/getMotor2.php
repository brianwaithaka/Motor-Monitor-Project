<?php

	$servername = "localhost";
	$username = "root";
	$password = "everly1";
	$dbname = "motormr";

	// Create connection
	$conn = mysqli_connect($servername, $username, $password, $dbname);
	if (!$conn) {
	  die("Connection failed: " . mysqli_connect_error());
	}

	//the SQL query to be executed
    $query = "SELECT * FROM `motor2` ORDER BY `ID` DESC LIMIT 200";
    //storing the result of the executed query
    $result = $conn->query($query);
	

    //initialize the array to store the processed data
    $jsonArray = array();
    //check if there is any data returned by the SQL Query
    if ($result->num_rows > 0) {
      //Converting the results into an associative array
      while($row = $result->fetch_assoc()) {
        $jsonArrayItem['ID'] = $row['ID'];
        $jsonArrayItem['Vibration2'] = $row['Vibration'];
		$jsonArrayItem['Temperature2'] = $row['Temperature'];
		$jsonArrayItem['DateTime'] = $row['Time'];
        //append the above created object into the main array.
        array_push($jsonArray, $jsonArrayItem);
      }
    }


    //Closing the connection to DB
    $conn->close();
    //set the response content type as JSON
    header('Content-type: application/json');
    //output the return value of json encode using the echo function.
    echo json_encode($jsonArray);

?>