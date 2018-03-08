<?php
 require_once 'shared.php';
 
 $idx = isset($_POST['idx']) ? $_POST['idx'] : '';
 
 
 
 switch($idx){
  case 1 : 
           $prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
		   $ta = isset($_POST['ta']) ? $_POST['ta'] : "";
		   $noktp = isset($_POST['noktp']) ? $_POST['noktp'] : "";
		   $vwkrs=new vw_krs;
		   $alm=$vwkrs->krs_to_pdf($prodi,$ta,$noktp);
		   echo $alm; 
           //echo $vwkrs->krs_html;
		   break;
 }
?>