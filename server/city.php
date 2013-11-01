<?php
error_reporting(0);
define("LOC_MAC", 10000000);

$payload = json_decode(file_get_contents('php://input'), true);
if(!$payload) {
	$payload = json_decode("{\"1\": 223059460,\"2\": 1142525520}", true);
}	
$lat = $payload[1] / LOC_MAC;
$long = $payload[2] / LOC_MAC;

//$pebbleid = "ABC1234567";
$pebbleid = $_SERVER['HTTP_X_PEBBLE_ID'];
if(empty($pebbleid) || !$pebbleid) {
	$pebbleid = "AXX1234567";
}


$geojson = file_get_contents('http://maps.googleapis.com/maps/api/geocode/json?latlng=' . $lat . ',' . $long . '&sensor=false');
$geodata = json_decode($geojson, TRUE);
//$addcomp = $geodata["results"][0]["address_components"];
$jsonresult = $geodata["results"];
$i = 0;
$pc_idx = 0;
$sa_idx = -1;
foreach($jsonresult as $result){
   if($result["types"][0] == "street_address")
   {
	$sa_idx = $i;
	break;
   }
   else if($result["types"][0] == "route")
   {
	$sa_idx = $i;
	break;
   }
   else if($result["types"][0] == "postal_code")
	$pc_idx =$i;
   $i++;
}
$addcomp = $jsonresult[$sa_idx<0?$pc_idx:$sa_idx]["address_components"];

$country_idx = 0; 
$i = 0;
foreach ($addcomp as $componet){
   if($componet["types"][0] == "country")
   {
	$country_idx = $i;
	break;
   }
   $i++;
}

$district = $addcomp[$country_idx-3]["short_name"];
$city = $addcomp[$country_idx-2]["short_name"];
$prov = $addcomp[$country_idx-1]["short_name"];
$country = $addcomp[$country_idx]["short_name"];

$data[1] = $country;
$data[2] = $prov;
$data[3] = $city;
$data[4] = $district;


header('Content-Type: application/json, charset=utf-8');
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); 
header("Cache-Control: no-store, no-cache, must-revalidate"); 
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
print json_encode($data);


?>
