<?php

 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/admin_app/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/admin_app/';		
	} 
    else{
	  $base_path = $server . '/admin_app/';	 
	}  
 }
 
 

include_once $base_path."dt/dt_fak_jn_prodi.class.inc";
include_once $base_path."dt/dt_mhs.class.inc";
require_once $base_path."dt/dt_prodi.class.inc";
require_once $base_path."dt/dt_fak.class.inc";
require_once $base_path."view/vw_mhs.class.inc";
require_once $base_path."dt/dt_ctk_log.class.inc";
include_once "../basic_class/html_table.class.php";
require_once "../dompdf/dompdf_config.inc.php";


class vw_stat
{   var $dt;
    var $dt1;
	function vw_stat()
	{
	  	$this->dt = new dt_fak_jn_prodi;
        $this->dt1 = new dt_mhs;		
	}
	
	function summary_stat()
	{   
	    $txt="<center><H1>DATA STATISTIK</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>";
		
		$txt=$txt."<fieldset>";
		$txt=$txt."<legend>Data Statistik Per. Angkatan:</legend>";
		$txt=$txt."<div>";
			 $txt=$txt.$this->stat_angkatan('lst_stat_uns');					 
		$txt=$txt."</div>";
		$txt=$txt."</fieldset>";
	   
	   $txt=$txt."<fieldset>";
       $txt=$txt."<legend>Data Statistik Per Prodi :</legend>";  
       $txt=$txt."<div>";  
	   $txt=$txt.$this->entry_stat();
       $txt=$txt."</div>"; 	
       $txt=$txt."</fieldset>";
	   
	   
	    $txt=$txt."<fieldset>";
        $txt=$txt."<legend>Mahasiswa Login Hari Ini:</legend>";  
        $txt=$txt."<div>";  
         	$vwmhs = new vw_mhs; 
	    $txt=$txt.$vwmhs->entry_data2(3);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>"; 
		
		$txt=$txt."<fieldset>";
        $txt=$txt."<legend>Mahasiswa Update Data Hari Ini:</legend>";  
        $txt=$txt."<div>";  
         	$vwmhs = new vw_mhs; 
	    $txt=$txt.$vwmhs->entry_data2(2);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>";
		
		$txt=$txt."<fieldset>";
        $txt=$txt."<legend>Mahasiswa Buat Akun Hari Ini:</legend>";  
        $txt=$txt."<div>";  
         	$vwmhs = new vw_mhs; 
	    $txt=$txt.$vwmhs->entry_data2(1);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>";
		
		
	   
	   
	   
	   return $txt;
	
	}
	
	function stat_angkatan($tb_label,$kd_prodi="",$kd_fak="")
	{
	     $TA = array(2008,2009,2010,2011,2012,2013);
         $jml=array(0,0,0,0,0,0,0,0,0,0);
         	
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $tb_label,"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('Angkatan', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));
	    $tbl->addCell('Total', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));	   
		$tbl->addCell('Kelas', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"2"));	    
        $tbl->addCell('Status Awal', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"2"));
		$tbl->addCell('Verifikasi', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"5"));
	    $tbl->addRow();
        $tbl->addCell('Reguler', null, 'header');	    
        $tbl->addCell('Non Reguler', null, 'header');
	    $tbl->addCell('Baru', null, 'header');	    
        $tbl->addCell('Pindahan', null, 'header');
        $tbl->addCell('Belum Layak', null, 'header');
		$tbl->addCell('Layak', null, 'header');
		$tbl->addCell('Sedang', null, 'header');
		$tbl->addCell('Lolos', null, 'header');	    
        $tbl->addCell('Tidak', null, 'header');		
		
		$where="";
		if($kd_fak!="")
		{
		 $where='kd_fakultas="'.$kd_fak.'"';
		}else{
		  if($kd_prodi!="")
			{
			 $where='kd_prodi="'.$kd_prodi.'"';
			}		
		}
		
		
		$data = $this->dt1->getdataStat($where);
		
		if(!empty($data))
		{
		  foreach($data as $row)
		  {
		    $tbl->addRow();
		    $tbl->addCell($row['Tahun_masuk'], null, 'data');
			$tbl->addCell($row['jmlttl'], null, 'data');
			$jml[0]=$jml[0]+$row['jmlttl'];
			$tbl->addCell($row['jmlR'], null, 'data');
			$jml[1]=$jml[1]+$row['jmlR'];
			$tbl->addCell($row['jmlN'], null, 'data');
			$jml[2]=$jml[2]+$row['jmlN'];
			$tbl->addCell($row['jmlB'], null, 'data');
			$jml[3]=$jml[3]+$row['jmlB'];
			$tbl->addCell($row['jmlP'], null, 'data');
			$jml[4]=$jml[4]+$row['jmlP'];
			$tbl->addCell($row['jmlblmlyk'], null, 'data');
			$jml[5]=$jml[5]+$row['jmlblmlyk'];
			$tbl->addCell($row['jmlval'], null, 'data');
			$jml[6]=$jml[6]+$row['jmlval'];
			$tbl->addCell($row['jmlsdver'], null, 'data');
			$jml[7]=$jml[7]+$row['jmlsdver'];
			$tbl->addCell($row['jmlver'], null, 'data');
			$jml[8]=$jml[8]+$row['jmlver'];
			$tbl->addCell($row['jmlnotver'], null, 'data');	
            $jml[9]=$jml[9]+$row['jmlnotver'];			
		  }
		
		}
		
		            $txt = '';
					$txt = $txt."<tr>";
						$txt = $txt."<th >Total</th>";
						//$txt = $txt."<th >".$jml_ttl."</th>";	
						for ($i = 0; $i <= 9; $i++) {
						   $txt = $txt."<th >".$jml[$i]."</th>";
						}											
					$txt = $txt."</tr>";				
					
	  return $tbl->display($txt);
	}
	
	function entry_stat($fak="")
	{
	    
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('Fak.', null, 'header');
	    $tbl->addCell('Prodi', null, 'header');	   
		$tbl->addCell('Jml. Mhs.', null, 'header');
	    $tbl->addCell('Layak Verifikasi', null, 'header');
		$tbl->addCell('Sedang Verifikasi', null, 'header');
		$tbl->addCell('Lolos Verifikasi', null, 'header');	 
	    	    
        $jml_input=0;
	    $jml_isi_nim=0;
	    $jml_update=0;
		$jml_verifikasi=0;
		
		$sql="";
		if($fak!="")
		{
		  $sql="tmst_prodi.kd_fakultas='".$fak."'";
		}
		
		$data = $this->dt1->getdataStat1($sql); 
		 if(!empty($data))
      {	 
		foreach($data as $row)
		{
		  $tbl->addRow();        
		 
		  $tbl->addCell($row['fakultas'], null, 'data');
	       $link='javascript:rekap_prodi("'.$row['kd_prodi'].'");';
		  $tbl->addCell("<a href='".$link."'>".$row['prodi']."</a>", null, 'data');	
          
		  $jml1 =$row['jmlttl'];
		  $tbl->addCell($jml1, null, 'data');
		   
		  $jml2 =$row['jmlval'];
		  $tbl->addCell($jml2, null, 'data');
          
		  $jml3 =$row['jmlsdver'];;
		  $tbl->addCell($jml3, null, 'data');
		  
		  $jml4 =$row['jmlver'];;
		  $tbl->addCell($jml4, null, 'data');
		  
		 $jml_input=$jml_input+$jml1;
		 $jml_isi_nim=$jml_isi_nim+$jml2;
		 $jml_update=$jml_update+$jml3;
		 $jml_verifikasi=$jml_verifikasi+$jml4;
         		  
		} 
      }
                    $txt = '';
					$txt = $txt."<tr>";
						$txt = $txt."<th colspan='2' align='center' >Total</th>";
						$txt = $txt."<th >".$jml_input."</th>";	
						$txt = $txt."<th >".$jml_isi_nim."</th>";
						$txt = $txt."<th >".$jml_update."</th>";
                        $txt = $txt."<th >".$jml_verifikasi."</th>";						
					$txt = $txt."</tr>";	
					
	  return $tbl->display($txt);
	}
	
	function stat_prodi_angkatan($kd_prodi,$id_opt)
	{
	 
	   $dt_prodi = new dt_prodi;
	   $data1 =  $dt_prodi->getData("kd_prodi = '".$kd_prodi."'");
	   
	   
	   
	   foreach($data1 as $row1)
	   {
	   $txt="<fieldset>";
	   $txt=$txt."<legend>Data Statistik Prodi. ".$row1['prodi'].":</legend>";
	   $txt=$txt."<div>";
					
          $txt=$txt.$this->stat_angkatan('lst_stat',$row1['kd_prodi']);					
					
	   $txt=$txt."</div>";
	   $txt=$txt."</fieldset>";
	   }
	   
	   $txt=$txt."</fieldset>";
		
		$txt=$txt."<fieldset>";
        $txt=$txt."<legend>Data Prodi. ".$row1['prodi'].":</legend>";  
        $txt=$txt."<div>";  
         
		 $vwmhs = new vw_mhs; 
	     $txt=$txt.$vwmhs->entry_data($kd_prodi,$id_opt);
         
		 $txt=$txt."</div>";	
         $txt=$txt."</fieldset>";
	   
	   $txt="<center><H1>REKAP DATA<BR>Prodi ".$row1['prodi']."</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>".$txt;
	   
	   return $txt;
	
	}
	
	
	
	
	
	
	function summary_stat_mng_to_pdf($userid)
	{   
	    
		$TA = array(2008,2009,2010,2011,2012,2013);
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
		
		$txt="<center><H1>REKAPITULASI<BR> PENDATAAN ULANG MAHASISWA (PUMHS)<br>ONLINE</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>";
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat_uns","width"=>"100%","border"=>"1"));
		
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
				
				$tbl->addCell($jml1, null, 'data',array("align"=>"right","style"=>"padding-right:3px"));
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data',array("align"=>"right","style"=>"padding-right:3px"));
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
		   }		
		}
		
		 $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th colspan='2'>Total</th>";	
						foreach ($TA as $ta) {
						  $txt1 = $txt1."<th align='right' style='padding-right:3px'>".$jml_ta[$ta]."</th>";											
						}						
						$txt1 = $txt1."<th align='right' style='padding-right:3px'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
		
		$txt=$txt."<div>";
			 $txt=$txt.$tbl->display($txt1);					 
		$txt=$txt."</div>";
		$txt=$txt."Keterangan : <br>";
        
		$txt2 = "<ul>";
		//$txt2 = $txt2."<li> Data belum di verifikasi Prodi dan Fakultas </li>";
		$txt2 = $txt2."<li> Data belum di klasifikasi Pusat dan KBB </li>";
		$txt2 = $txt2."</ul>";
		  
		  
		 $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","align"=>"right"));
		 $tbl1->addRow();
		 $tbl1->addCell("Baleendah, .... - .......... - ......", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("Ketua TIM PSI", null, 'data',array("align"=>"center"));
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("( ................... )", null, 'data',array("align"=>"center")); 
         $txt2 = $txt2."<br><br>".$tbl1->display("");         

		 
		  $server = $_SERVER['DOCUMENT_ROOT'];
          $base_path = $server . '/admin_app/cetak/';
			 if(!is_dir($base_path)){
			   if($server=="/home/uni10000/public_html/pumhs") {
					$base_path = $server . '/admin_app/cetak/';		
				} 
				else{
				  $base_path = $server . '/admin_app/cetak/';	 
				}  
		    }
		  
		  
		  
		  $tmp = "stat - ".date("dmY His").".pdf";
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt.$txt2);
          $dompdf->set_paper('a4', 'landscape');
		  $dompdf->render();
          $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_ctk_log = new dt_ctk_log;		  
		  $dt_ctk_log->insert($tmp,$userid); 

          if($server=="/home/uni10000/public_html/pumhs") {
            $base_path="http://pumhs.unibba.ac.id/admin_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		return $base_path.$tmp;
	
	}
}
?>












