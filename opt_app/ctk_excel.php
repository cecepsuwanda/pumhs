<?php
 
 require_once "shared.php";
 
 $idx = isset($_POST['idx']) ? $_POST['idx'] : '';
 $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
 
 
 switch($idx){
  case 1 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['sem']) ? $_POST['sem'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->DHMD_to_excel($fak,$prodi,$thn,$id_opt); 
           break;}
?>