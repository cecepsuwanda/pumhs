<?php 
session_start();

error_reporting(E_ALL & ~E_WARNING);

include_once("view/vw_mhs.class.inc");
include_once("view/vw_stat.class.inc");
include_once("view/vw_log.class.inc");
include_once("dt/dt_admin_log.class.inc");

$idx = $_POST['idx'];

switch($idx){
case 1 :    $vwstat = new vw_stat; 
            echo $vwstat->summary_stat();
            break;  
			
case 2 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->list_mhs();
                        break;          

case 3 :   
                    $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
                    $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
                    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";                   
                        
                    $vwmhs = new vw_mhs;             
                    echo $vwmhs->filter_list_mhs($fak,$prodi,$thn);
                    break;
                        
                        
case 4 :    
            $noktp = $_POST['noktp'];
			$vwmhs = new vw_mhs; 
            echo $vwmhs->data_mhs($noktp);
			break; 

case 5 :    $vwmhs = new vw_mhs;            
			echo $vwmhs->filter_verifikasi();
			break;
case 6 :   
			
			$nmfile = isset($_POST['nmfile']) ? $_POST['nmfile'] : "";
		    $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($prodi,$thn,$idx1,$nmfile);
			break;			
			
case 7 :    
            $username = $_SESSION["userName"];
            $lg_time = $_SESSION["lg_time"];
	        $dt=new dt_admin_log;
			$dt->logout($lg_time,$username);
			break;

case 8 :   
			$vwmhs = new vw_mhs; 
            echo $vwmhs->persiapan_kuliah();
			break;
			
case 9 :   
			
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$ta = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($prodi,$thn,$idx1,"",$ta);
			break;			
			
case 10 :   
             $kd_prodi = $_POST['kd_prodi'];
			 $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
             $vwstat = new vw_stat; 
	         echo $vwstat->stat_prodi_angkatan($kd_prodi,$id_opt);
             break;			
case 11 : 
          $vwlog = new vw_log; 
          echo $vwlog->lst_log();
          break;
case 12 : $vwlog = new vw_log; 
          echo $vwlog->ctk_log();
          break;


		  
		  
			
}			

?>