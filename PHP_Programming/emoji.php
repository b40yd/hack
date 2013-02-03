<?php
include_once(dirname(__FILE__).'/cnsubstr.php');

/**
* emoji is feature phone face.
* emoji function resolve the face of user input return HEX
* for example:
*  $filter = array(1=>'bac3',2=>'6c6c');
*	$nis = "你好hello";
*	echo emoji($nis); =>  你\&\#bac3\&\#6c6cello
*/


$filter = array(1=>'bac3',2=>'6c6c');

function emoji($str){
	Global $filter ;
	$tmpArr = $acsii = array();
	$s = '';
	 array();
	$strToArray = str_split($str);
	foreach($strToArray as $i=>$v){
		if($i % 2 ==0){
			if(isset($strToArray[$i+1])){
				$s = dechex(ord($strToArray[$i])).dechex(ord($strToArray[$i+1]));
				//var_dump($s);
				if(in_array($s,$filter)){
					$index = ($i/2);
					if($index != 0){
						$tmpArr = array($index=>$s);
						array_push($acsii,$tmpArr); //will push string index and HEX code.
					}
				
				}
			}
		}
	}
	
	$newStr = $str;
	foreach ($acsii as $asi){
		foreach($asi as $k=>$v){
			$newStr = str_replace( cnsubstr($str,$k+1,1),"\&\#".$v,$newStr);
		}
	}
	return $newStr;
}

$nis = "你好hello";
echo emoji($nis)."<hr>";
?>
