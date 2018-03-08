<?php
 session_start();
 
 include_once("view/vw_stat.class.inc");
 
 $idx = isset($_POST['idx']) ? $_POST['idx'] : '';
 
 switch($idx){
  case 1 : 
           $userid = $_SESSION["userName"];
		   $vwstat=new vw_stat;
		   echo $vwstat->summary_stat_mng_to_pdf($userid); 
           break; 
 
 }
?>