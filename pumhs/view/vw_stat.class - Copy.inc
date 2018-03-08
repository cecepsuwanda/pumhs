<?php

 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/pumhs/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/pumhs/';		
	} 
    else{
	  $base_path = $server . '/pumhs/';	 
	}  
 }
 
 

include_once $base_path."dt/dt_fak_jn_prodi.class.inc";
include_once $base_path."dt/dt_mhs.class.inc";
require_once $base_path."dt/dt_prodi.class.inc";
require_once $base_path."dt/dt_fak.class.inc";
include_once "basic_class/html_table.class.php";



class vw_stat
{   var $dt;
    var $dt1;
	function vw_stat()
	{
	  	$this->dt = new dt_fak_jn_prodi;
        $this->dt1 = new dt_mhs;		
	}
	
		function summary_stat_mng()
	{   
	    
		$TA = array(2008,2009,2010,2011,2012,2013);
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$txt="<center><H1>REKAPITULASI<BR> PENDATAAN ULANG MAHASISWA (PUMHS)<br>ONLINE</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>";
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
		
		
		$dt_fk = new dt_fak;
		$data = $dt_fk->getData("");
		if(!empty($data))
        {	
		   $i=1;
		   
		   foreach($data as $row)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($row['fakultas'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    
				$sql = "tahun_masuk=".$ta." AND kd_fakultas='".$row['kd_fakultas']."'";
				
				$jml1 = $this->dt1->getJml($sql);
				
				$tbl->addCell($jml1, null, 'data');
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data');
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='left'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<fieldset><legend>Data Masuk :</legend><div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div></fieldset><br>";
		
		
		
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns1","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
		
		
		$dt_fk = new dt_fak;
		$data = $dt_fk->getData("");
		if(!empty($data))
        {	
		   $i=1;
		   
		   foreach($data as $row)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($row['fakultas'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    
				$sql = "tahun_masuk=".$ta." AND kd_fakultas='".$row['kd_fakultas']."' and validasi=0 and verifikasi=0 and nm_file=''";
				
				$jml1 = $this->dt1->getJml($sql);
				
				$tbl->addCell($jml1, null, 'data');
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data');
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='left'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<fieldset><legend>Data Belum Layak Verifikasi :</legend><div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div></fieldset><br>";
		
		
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns2","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
		
		
		$dt_fk = new dt_fak;
		$data = $dt_fk->getData("");
		if(!empty($data))
        {	
		   $i=1;
		   
		   foreach($data as $row)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($row['fakultas'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    
				$sql = "tahun_masuk=".$ta." AND kd_fakultas='".$row['kd_fakultas']."' and validasi=1 and verifikasi=0 and nm_file=''";
				
				$jml1 = $this->dt1->getJml($sql);
				
				$tbl->addCell($jml1, null, 'data');
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data');
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='left'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<fieldset><legend>Data Layak Verifikasi :</legend><div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div></fieldset><br>";
		
		
		
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns3","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
		
		
		$dt_fk = new dt_fak;
		$data = $dt_fk->getData("");
		if(!empty($data))
        {	
		   $i=1;
		   
		   foreach($data as $row)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($row['fakultas'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    
				$sql = "tahun_masuk=".$ta." AND kd_fakultas='".$row['kd_fakultas']."' and verifikasi=0 and nm_file<>''";
				
				$jml1 = $this->dt1->getJml($sql);
				
				$tbl->addCell($jml1, null, 'data');
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data');
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='left'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<fieldset><legend>Data Sedang Diverifikasi :</legend><div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div></fieldset><br>";
		
		
		
		
		
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns4","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
		
		
		$dt_fk = new dt_fak;
		$data = $dt_fk->getData("");
		if(!empty($data))
        {	
		   $i=1;
		   
		   foreach($data as $row)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($row['fakultas'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    
				$sql = "tahun_masuk=".$ta." AND kd_fakultas='".$row['kd_fakultas']."' and verifikasi=1";
				
				$jml1 = $this->dt1->getJml($sql);
				
				$tbl->addCell($jml1, null, 'data');
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data');
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='left'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<fieldset><legend>Data Lolos Verifikasi :</legend><div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div></fieldset><br>";		
		
		
		$txt=$txt."Keterangan : <br>";
        
		$txt2 = "<ul>";
		//$txt2 = $txt2."<li> Data belum di verifikasi Prodi dan Fakultas </li>";
		$txt2 = $txt2."<li> Data belum di klasifikasi Pusat dan KBB </li>";
		$txt2 = $txt2."</ul>";
		
		return $txt.$txt2;
	
	}
	
}
?>












