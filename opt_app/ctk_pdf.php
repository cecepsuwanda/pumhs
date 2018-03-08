<?php
 
 require_once("shared.php");
 
 $idx = isset($_POST['idx']) ? $_POST['idx'] : '';
 $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
 
 
 switch($idx){
  case 1 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['thn']) ? $_POST['thn'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->Data_to_pdf($fak,$prodi,$thn,$id_opt); 
           break;
  case 2 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['thn']) ? $_POST['thn'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->Data_verifikasi_to_pdf($fak,$prodi,$thn,$id_opt); 
           break;

  case 3 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['thn']) ? $_POST['thn'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->Data_hsl_verifikasi_to_pdf($fak,$prodi,$thn,$id_opt); 
           break;	
  case 4 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['thn']) ? $_POST['thn'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->Data_blmlyk_verifikasi_to_pdf($fak,$prodi,$thn,$id_opt); 
           break;
  case 5 : 
           $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		   $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		   $thn = isset($_POST['thn']) ? $_POST['thn'] : "";
		   $vwmhs=new vw_mhs;
		   echo $vwmhs->Data_absperwalian_to_pdf($fak,$prodi,$thn,$id_opt); 
           break;		   
  case 6 : $prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
		   $ta = isset($_POST['ta']) ? $_POST['ta'] : "";
		   $noktp = isset($_POST['noktp']) ? $_POST['noktp'] : "";
		   $vwkrs=new vw_krs;
		   echo $vwkrs->krs_to_pdf($prodi,$ta,$noktp); 
           break;
   case 7 : $prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
		   $ta = isset($_POST['ta']) ? $_POST['ta'] : "";
		   $noktp = isset($_POST['noktp']) ? $_POST['noktp'] : "";
		   $vwkrs=new vw_krs;
		   echo $vwkrs->khs_to_pdf($prodi,$ta,$noktp); 
           break;        		   
 
 }
?>