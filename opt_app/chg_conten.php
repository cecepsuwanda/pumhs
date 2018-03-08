<?php 
 require_once 'shared.php';

$idx = $_POST['idx'];

switch($idx){
 	
case 3 :    $vwmhs = new vw_mhs; 
            $fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
			echo $vwmhs->list_mhs($fak,$id_opt);
			break;
	
case 4 :    
            $noktp = $_POST['noktp'];
			$vwmhs = new vw_mhs; 
            echo $vwmhs->data_mhs($noktp);
			break;	
	
case 5 :    $vwstat = new vw_stat; 
            $fak = isset($_POST['fak']) ? $_POST['fak'] : "";  
	        echo $vwstat->summary_opt_stat($fak);
			break;
case 6 :    
            $id_opt = $_SESSION["id_opt"];
            $lg_time = $_SESSION["lg_time"];
	        $dt=new dt_opt_log;
			$dt->logout($lg_time,$id_opt);
			break;			
			
case 8 :    
            $kd_fak = isset($_POST['kd_fak']) ? $_POST['kd_fak'] : "";
			$kd_prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
			$vwmhs = new vw_mhs; 
            echo $vwmhs->input_data_mhs($kd_fak,$kd_prodi);
			break;
case 9 :    
            $noktp = $_POST['noktp'];
			$kd_fak = isset($_POST['kd_fak']) ? $_POST['kd_fak'] : "";
			$vwmhs = new vw_mhs; 
            echo $vwmhs->edit_data_mhs($noktp,$kd_fak);
			break; 			
			
case 10 :   
             $kd_prodi = $_POST['kd_prodi'];
			 $kd_fak = isset($_POST['kd_fak']) ? $_POST['kd_fak'] : "";
			 $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
             $vwstat = new vw_stat; 
	         echo $vwstat->stat_prodi_angkatan($kd_prodi,$id_opt,$kd_fak);
             break;			
case 11 :    $vw_operator= new vw_operator;
             echo $vw_operator->vw_change_pass(); 
             break;	
case 12 :    
             $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
			 $kd_fak = isset($_POST['fak']) ? $_POST['fak'] : "";
             $vwlog = new vw_log; 
             echo $vwlog->ctk_log($kd_fak,$id_opt); 
             break;			 
case 13 :    $noktp = $_POST['noktp'];
             $vwmhs = new vw_mhs;
             echo $vwmhs->cekKTP($noktp);
             break;
			 
case 14 :   $vwmhs = new vw_mhs; 
            $kd_fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			echo $vwmhs->filter_verifikasi($kd_fak);
			break;	
case 15 :   
			$vwmhs = new vw_mhs; 
            $kd_fak = isset($_POST['fak']) ? $_POST['fak'] : "";
            echo $vwmhs->persiapan_kuliah($kd_fak);
			break;
case 16 :   
			$fak = isset($_POST['fak']) ? $_POST['fak'] : "";
		    $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"] : "";
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->filter_list_mhs($fak,$id_opt,$prodi,$thn);
			break;
case 17 :   
			$fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			$nmfile = isset($_POST['nmfile']) ? $_POST['nmfile'] : "";
		    $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($fak,$prodi,$thn,$idx1,$nmfile);
			break;			
case 18 :   
			$fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$ta = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($fak,$prodi,$thn,$idx1,"",$ta);
			break;	

case 19 :   
			
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $ta = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$nta = isset($_POST['nta']) ? $_POST['nta'] : "";
			$noktp=isset($_POST['noktp']) ? $_POST['noktp'] : "";
			$vwmtk = new vw_mtk; 
            echo $vwmtk->tbl_krs_mdl1($prodi,$ta,$nta,$noktp);
			break;

case 20 :   
			
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $sem = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$kode=isset($_POST['kode']) ? $_POST['kode'] : "";
			$shift=isset($_POST['shift']) ? $_POST['shift'] : "";
			$kelas=isset($_POST['kelas']) ? $_POST['kelas'] : "";
			$fak=isset($_POST['fak']) ? $_POST['fak'] : "";
			$vwkrs = new vw_krs; 
            echo $vwkrs->list_nilai($prodi,$sem,$kode,$shift,$kelas,$fak);
			break;						

case 21 :   
			$fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$ta = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($fak,$prodi,$thn,$idx1,"",$ta);
			break;

case 22 :   
			$fak = isset($_POST['fak']) ? $_POST['fak'] : "";
			$prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
		    $thn = isset($_POST['thn']) ? $_POST['thn'] : "";			
			$idx1=isset($_POST['idx1']) ? $_POST['idx1'] : "";
			$ta = isset($_POST['sem']) ? $_POST['sem'] : 0;
			$vwmhs = new vw_mhs;             
			 echo $vwmhs->hsl_filter($fak,$prodi,$thn,$idx1,"",$ta);
			break;							
			
}			

?>