<?php
$data =  array(
	array (
		'id' => 1,
		'pid' => 0,
		'name'=>'test1'
	),
	array (
		'id' => 2,
		'pid' => 1,
		'name'=>'test2'
	),
	array (
		'id' => 3,
		'pid' => 1,
		'name'=>'test3'
	),
	array (
		'id' => 4,
		'pid' => 0,
		'name'=>'test4'
	),
	array (
		'id' => 5,
		'pid' => 0,
		'name'=>'test5'
	),
	array (
		'id' => 6,
		'pid' => 4,
		'name'=>'test6'
	),
	array (
		'id' => 7,
		'pid' => 4,
		'name'=>'test7'
	),
	array (
		'id' => 8,
		'pid' => 5,
		'name'=>'test8'
	),
	array (
		'id' => 9,
		'pid' => 8,
		'name'=>'test9'
	),

);

function tree(array $list,$id = 'id',$parent = 'pid',$child='_child',$root=0){
	$tree = $refer = array();
	if(!empty($list)){
		foreach($list as $key => $data){
			$refer[$data[$id]] = &$list[$key];
		}
		
		foreach($list as $key => $data){
			if($root == $data[$parent]){
				$tree[] =& $list[$key];	
			}else{
				if(isset($refer[$data[$parent]])){	
					$parents =& $refer[$data[$parent]];
					$parents[$child][] =& $list[$key];
				}
			}
		}
	}
	unset($refer,$parents);
	return $tree;
}

$dd= tree($data);
foreach($dd as $d){
	var_dump(isset($d['_child'])?$d['_child']:null);
	foreach($d['_child'] as $s){
		var_dump(isset($s['_child'])?$s['_child']:null);
	}
}
?>
