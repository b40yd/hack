<?php



function getTimeZone($nowTime,$resetTime){

  $resetTimeArray = explode(':',$resetTime);
  $nowTimeArray = explode(' ',$nowTime);
  $nowTimeArray0 = explode('/',$nowTimeArray[0]);
  $nowTimeArray1 = explode(':',$nowTimeArray[1]);

  $timeZone = array();
  $timeZonePre = array();
  $timeZoneNex = array();

  if( $resetTimeArray[0]>$nowTimeArray1[0] ){

    // pre day
    $timeZone[] = mktime($resetTimeArray[0],$resetTimeArray[1],0,
			 $nowTimeArray0[1], (string)($nowTimeArray0[2]-1), $nowTimeArray0[0]);

    // now day
    $timeZone[] = mktime($resetTimeArray[0],$resetTimeArray[1],0,
			 $nowTimeArray0[1], $nowTimeArray0[2], $nowTimeArray0[0]);

  }else{

    // pre day
    $timeZone[] = mktime($resetTimeArray[0],$resetTimeArray[1],0,
			 $nowTimeArray0[1], $nowTimeArray0[2], $nowTimeArray0[0]);

    // now day
    $timeZone[] = mktime($resetTimeArray[0],$resetTimeArray[1],0,
			 $nowTimeArray0[1], (string)($nowTimeArray0[2]+1), $nowTimeArray0[0]);

  }

  return $timeZone;
}



function isInTimeZone($nearTime,$nowTime,$timeZone){

  if( $nearTime >= $timeZone[0] && $nearTime < $timeZone[1] && $nowTime < $timeZone[1] ){
    return true;
  }else{
    return false;
  }

}



$resetTime = '12:00';
// $prayNumArray from your data
$nowDateTime = time();
$timeZone = getTimeZone( date('y/m/d H:i',$nowDateTime), $resetTime);
$lastTime = 0;
$existPrayNum = 1;


while ($existPrayNum < 3){
  //get last time,lastTime is not null,Assignment to give it
  if(isInTimeZone( $lastTime, $nowDateTime, $timeZone)){
    if($existPrayNum < 3){
      echo $existPrayNum."<br>";

    }
  }else{
    //get last time 
    if($lastTime == 0)
      $lastTime = time();
    $existPrayNum = 0;
    echo "0<br>";
  }

  echo "10<br>";
  $existPrayNum++;
}

?>