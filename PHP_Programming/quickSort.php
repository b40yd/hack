<?php
class a{
  private $s = 0;

  public function __construct($a){
    $this->s = $a;
  }

  public function getGachaBasePriority(){
    return $this->s;
  }

  public function setGachaBasePriority($a){
    $this->s=$a;
  }

}

$as = array();
for($i = 0;$i<=10;$i++){

  array_push($as,new a(rand(1,9)));
}


function getGachaSortByPriorityLevel(Array $gachaObjectArray){
  if (count($gachaObjectArray) == 0)
    return array();
  $pivot = $gachaObjectArray[0];
  $left = $right = array();
  for ($i = 1; $i < count($gachaObjectArray); $i++) {
    if ($gachaObjectArray[$i]->getGachaBasePriority() < $pivot->getGachaBasePriority())
      $left[] = $gachaObjectArray[$i];
    else
      $right[] = $gachaObjectArray[$i];
  }
  return array_merge(quicksort($left), array($pivot), quicksort($right));
}

var_dump($as);
var_dump(date("m/d/Y H:i",time()));
var_dump(getGachaSortByPriorityLevel($as))

?>