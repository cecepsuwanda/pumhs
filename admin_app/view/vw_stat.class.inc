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
require_once '../PHPExcel/PHPExcel.php';

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
	
	
	function buattbl($lst,$lbl)
	{
		
		$TA = array(2008,2009,2010,2011,2012,2013);
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
				
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $lbl,"width"=>"100%","border"=>"1"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>'6'));
		$tbl->addCell('Total', null, 'header',array('rowspan'=>'2'));
		$tbl->addRow();   
		foreach ($TA as $dt) {
		  $tbl->addCell($dt, null, 'header');
	    } 
				
		
		if(!empty($lst))
        {	
		   $i=1;
		   
		   foreach($lst as $key => $val)
		   {
		    $tbl->addRow();
			$tbl->addCell($i, null, 'data');
			$tbl->addCell($val['nm_fak'], null, 'data');
			$jml_total=0;
			foreach ($TA as $ta) {
			    								
				$jml1 = isset($val[$ta]) ? $val[$ta]:0;
				
				$tbl->addCell($jml1, null, 'data',array('align'=>'right'));
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
			}
			$tbl->addCell($jml_total, null, 'data',array('align'=>'right'));
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
						$txt1 = $txt1."<th align='right'>".$jml_un."</th>";
		                $txt1 = $txt1."</tr>";
	    
		return $tbl->display($txt1);
	
	}
	
	
	function summary_stat_mng()
	{   
	    
		
		$data = $this->dt1->getdataStat2("");
		
		if(!empty($data))
        { $kd_fak=""; 
		  foreach($data as $row)
		  {
		    
			  $kd_fak=$row['kd_fakultas'];            
			  $jmlttl[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlttl[$kd_fak][$row['Tahun_masuk']]=$row['jmlttl'];
              $jmlblmlyk[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlblmlyk[$kd_fak][$row['Tahun_masuk']]=$row['jmlblmlyk'];
              $jmlval[$kd_fak]['nm_fak']=$row['fakultas'];	
			  $jmlval[$kd_fak][$row['Tahun_masuk']]=$row['jmlval'];	
              $jmlsdver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlsdver[$kd_fak][$row['Tahun_masuk']]=$row['jmlsdver'];	
              $jmlver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlver[$kd_fak][$row['Tahun_masuk']]=$row['jmlver'];
              $jmlnotver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlnotver[$kd_fak][$row['Tahun_masuk']]=$row['jmlnotver']; 			  
						
		  }
		}
		
		$dt_krs = new dt_krs;
		$data = $dt_krs->getDataStat("");
		
		if(!empty($data))
        { $kd_fak=""; 
		  foreach($data as $row)
		  {
		    
			  $kd_fak=$row['kd_fakultas'];            
			  $jmlkrs[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlkrs[$kd_fak][$row['Tahun_masuk']]=$row['jml'];
              						
		  }
		}
		$txt='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div>';
		$txt.='<span class="page">';		
		$txt.="<center><H1>REKAPITULASI<BR> PENDATAAN ULANG MAHASISWA (PUMHS)<br>ONLINE</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>";
		$txt=$txt."<H3>Data Masuk :</H3><br>";
		$txt=$txt.$this->buattbl($jmlttl,"lst_stat_uns");					 
		$txt.='<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div>';
		$txt.='</span>';		
		
		$txt.='<span class="page">';
		$txt=$txt."<H3>Data Belum Layak Verifikasi :</H3><br>";
		$txt=$txt.$this->buattbl($jmlblmlyk,"lst_stat_uns1");
		$txt=$txt."<br><H3>Data Layak Verifikasi :</H3><br>";
		$txt=$txt.$this->buattbl($jmlval,"lst_stat_uns2");					 
		$txt.='<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div>';
		$txt.='</span>';
		
		$txt.='<span class="page">';
		$txt=$txt."<H3>Data Sedang Diverifikasi :</H3><br>";
		$txt=$txt.$this->buattbl($jmlsdver,"lst_stat_uns3");					 
		$txt=$txt."<br><H3>Data Lolos Verifikasi :</H3><br>";
		$txt=$txt.$this->buattbl($jmlver,"lst_stat_uns4");					 
		$txt.='<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div>';
		$txt.='</span>';		
		
		$txt.='<span class="page">';
		$txt=$txt."<H3>Data KRS :</H3><br>";
		$txt=$txt.$this->buattbl($jmlkrs,"lst_stat_uns5");					 
					
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
         $txt2 = "<br>".$tbl1->display("");      
		 $txt=$txt.$txt2;
		 $txt.='<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div>';
		 $txt.='</span>';
		//<span class="page">'.$this->summary_stat_mng().'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
		
		return $txt;
	   
	}
	
	
	
	function summary_stat_mng_to_pdf($userid)
	{   
	  	 
		 $tabel=$this->summary_stat_mng();
		 
		 
		 $txt='<html><head>';
		 $txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 50px;  border-top: 2px solid gray;} .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		 $txt.='</head><body>';		
		 $txt.=$tabel;
		 $txt.='</body></html>';
		 
		 
		 
		 
		 
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
          $dompdf->load_html($txt);
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
	
	function buattbl_xls($Sheet,$norow,$lst,$lbl)
	{
		
		$TA = array(2008,2009,2010,2011,2012,2013);
		$jml_ta=array(2008=>0,2009=>0,2010=>0,2011=>0,2012=>0,2013=>0);
		$jml_un=0;
			
           
		$Sheet->setCellValue('A'.$norow, 'No.'); 
		$Sheet->mergeCells('A'.$norow.':A'.($norow+1));
		$Sheet->getStyle('A'.$norow.':A'.($norow+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('A'.$norow.':A'.($norow+1))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
				
		$Sheet->setCellValue('B'.$norow, 'Fakultas'); 
		$Sheet->mergeCells('B'.$norow.':B'.($norow+1));
		$Sheet->getStyle('B'.$norow.':B'.($norow+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('B'.$norow.':B'.($norow+1))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
			
		$Sheet->setCellValue('C'.$norow, 'Angkatan'); 
		$Sheet->mergeCells('C'.$norow.':H'.$norow);
		$Sheet->getStyle('C'.$norow.':H'.$norow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('C'.$norow.':H'.$norow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
				
		
		$Sheet->setCellValue('I'.$norow, 'Total'); 
		$Sheet->mergeCells('I'.$norow.':I'.($norow+1));
		$Sheet->getStyle('I'.$norow.':I'.($norow+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('I'.$norow.':I'.($norow+1))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
				 
		$i=0;
		foreach ($TA as $dt) {
		  $Sheet->setCellValue(chr(ord('C')+$i).($norow+1), $dt);
          $i+=1; 		  
	    } 
	      $Sheet->getStyle('C'.($norow+1).':H'.($norow+1))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		  $Sheet->getStyle('C'.($norow+1).':H'.($norow+1))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 
		  	
		$firstrow=$norow+2;
		if(!empty($lst))
        {	
		   $i=1;		   
		   foreach($lst as $key => $val)
		   {
		    			
			$Sheet->setCellValue('A'.$firstrow, $i); 
		    $Sheet->getStyle('A'.$firstrow.':A'.$firstrow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT); 
		    $Sheet->getStyle('A'.$firstrow.':A'.$firstrow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 
						
			$Sheet->setCellValue('B'.$firstrow, $val['nm_fak']); 
		    $Sheet->getStyle('B'.$firstrow.':B'.$firstrow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT); 
		    $Sheet->getStyle('B'.$firstrow.':B'.$firstrow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 
			
			
			
			$jml_total=0;
			$j=0;
			foreach ($TA as $ta) {
			    								
				$jml1 = isset($val[$ta]) ? $val[$ta]:0;								
				$Sheet->setCellValue(chr(ord('C')+$j).$firstrow, $jml1);		        			
				$jml_total=$jml_total+$jml1;
				$jml_ta[$ta]=$jml_ta[$ta]+$jml1;
				$j+=1;
			}
			    
			
			$Sheet->setCellValue('I'.$firstrow, $jml_total);
			$Sheet->getStyle('C'.$firstrow.':I'.$firstrow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT); 
		    $Sheet->getStyle('C'.$firstrow.':I'.$firstrow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 
					
			$jml_un=$jml_un+$jml_total;
			$i=$i+1;
			$firstrow+=1;
		   }		
		}
		
		 
							
						$Sheet->setCellValue('A'.$firstrow, 'Total'); 
		                $Sheet->mergeCells('A'.$firstrow.':B'.$firstrow);
		                $Sheet->getStyle('A'.$firstrow.':B'.$firstrow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		                $Sheet->getStyle('A'.$firstrow.':B'.$firstrow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
		
						
						$j=0;
						foreach ($TA as $ta) {
						  $Sheet->setCellValue(chr(ord('C')+$j).$firstrow, $jml_ta[$ta]);						  
						  $j+=1;
						}						
						
		                $Sheet->setCellValue('I'.$firstrow, $jml_un); 
		                $Sheet->getStyle('C'.$firstrow.':I'.$firstrow)->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT); 
		                $Sheet->getStyle('C'.$firstrow.':I'.$firstrow)->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
		
		                $Sheet->getStyle('A'.$norow.':I'.($norow+1))->applyFromArray(
												array(	
													'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);
						
						$Sheet->getStyle('A'.($norow+2).':I'.($firstrow-1))->applyFromArray(
												array(	
													'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);
											
						$Sheet->getStyle('A'.$firstrow.':I'.$firstrow)->applyFromArray(
												array(	
													'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);					
		
		
	    
		return $Sheet;
	
	}
	
	
	function summary_stat_mng_xls($Sheet)
	{   
	    
		
		$data = $this->dt1->getdataStat2("");
		
		if(!empty($data))
        { $kd_fak=""; 
		  foreach($data as $row)
		  {
		    
			  $kd_fak=$row['kd_fakultas'];            
			  $jmlttl[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlttl[$kd_fak][$row['Tahun_masuk']]=$row['jmlttl'];
              $jmlblmlyk[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlblmlyk[$kd_fak][$row['Tahun_masuk']]=$row['jmlblmlyk'];
              $jmlval[$kd_fak]['nm_fak']=$row['fakultas'];	
			  $jmlval[$kd_fak][$row['Tahun_masuk']]=$row['jmlval'];	
              $jmlsdver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlsdver[$kd_fak][$row['Tahun_masuk']]=$row['jmlsdver'];	
              $jmlver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlver[$kd_fak][$row['Tahun_masuk']]=$row['jmlver'];
              $jmlnotver[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlnotver[$kd_fak][$row['Tahun_masuk']]=$row['jmlnotver']; 			  
						
		  }
		}
		
		$dt_krs = new dt_krs;
		$data = $dt_krs->getDataStat("");
		
		if(!empty($data))
        { $kd_fak=""; 
		  foreach($data as $row)
		  {
		    
			  $kd_fak=$row['kd_fakultas'];            
			  $jmlkrs[$kd_fak]['nm_fak']=$row['fakultas'];
			  $jmlkrs[$kd_fak][$row['Tahun_masuk']]=$row['jml'];
              						
		  }
		}
		
		               $Sheet->getColumnDimension('A')->setWidth(3.00);
		               $Sheet->getColumnDimension('B')->setWidth(45.00);
					   $Sheet->getColumnDimension('C')->setWidth(8.00);
					   $Sheet->getColumnDimension('D')->setWidth(8.00);
					   $Sheet->getColumnDimension('E')->setWidth(8.00);

					   $Sheet->getColumnDimension('F')->setWidth(8.00);
					   $Sheet->getColumnDimension('G')->setWidth(8.00);
					   $Sheet->getColumnDimension('H')->setWidth(8.00);
					   $Sheet->getColumnDimension('I')->setWidth(8.00);
				
		$Sheet->setCellValue('A1', 'REKAPITULASI'); 
		$Sheet->mergeCells('A1:I1');
		$Sheet->getStyle('A1:I1')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('A1:I1')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
		
		$Sheet->setCellValue('A2','PENDATAAN ULANG MAHASISWA (PUMHS)');
		$Sheet->mergeCells('A2:I2');
		$Sheet->getStyle('A2:I2')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('A2:I2')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
		
		$Sheet->setCellValue('A3','ONLINE');
		$Sheet->mergeCells('A3:I3');
		$Sheet->getStyle('A3:I3')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('A3:I3')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
		
		$Sheet->getStyle('A1:I3')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 12
							    )
							)
		);
		
		
		$Sheet->setCellValue('A5','Kondisi Data Pada Tanggal :'.date("Y-m-d H:i:s"));
		$Sheet->mergeCells('A5:I5');
		$Sheet->getStyle('A5:I5')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
		$Sheet->getStyle('A5:I5')->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
				
		
        $Sheet->getStyle('A5:I5')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => false,
							    'name'      => 'Times New Roman',
								'size'      => 9
							    )
							)
		);		
				
				
		$Sheet->setCellValue('A7','Data Masuk :');
		$Sheet->getStyle('A7:A7')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
		
		
		$this->buattbl_xls($Sheet,9,$jmlttl,"lst_stat_uns");					 
			
		$Sheet->setCellValue('A20','Data Belum Layak Verifikasi :');
		$Sheet->getStyle('A20:A20')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
				
		$this->buattbl_xls($Sheet,22,$jmlblmlyk,"lst_stat_uns1");
				
		$Sheet->setCellValue('A33','Data Layak Verifikasi :');
		$Sheet->getStyle('A33:A33')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
		
		
		$this->buattbl_xls($Sheet,35,$jmlval,"lst_stat_uns2");					 
				
		
		$Sheet->setCellValue('A46','Data Sedang Diverifikasi :');
		$Sheet->getStyle('A46:A46')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
		
		
		$this->buattbl_xls($Sheet,48,$jmlsdver,"lst_stat_uns3");					 
		
		$Sheet->setCellValue('A59','Data Lolos Verifikasi :');
		$Sheet->getStyle('A59:A59')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
		
		
		$this->buattbl_xls($Sheet,61,$jmlver,"lst_stat_uns4");					 
			
		$Sheet->setCellValue('A72','Data KRS :');
		$Sheet->getStyle('A72:A72')->applyFromArray(
						array(
								'font'    => array(
								'bold'      => true,
							    'name'      => 'Times New Roman',
								'size'      => 10
							    )
							)
		);
		
		$this->buattbl_xls($Sheet,74,$jmlkrs,"lst_stat_uns5");					 
					
		
		
		return $Sheet;
	   
	}
	
	
	function summary_stat_mng_to_excel($userid)
	{
	    
		$objPHPExcel = new PHPExcel();
		$Sheet = $objPHPExcel->getActiveSheet();
		
		 $this->summary_stat_mng_xls($Sheet);
		
		
		              $Sheet->getPageSetup()->setOrientation(PHPExcel_Worksheet_PageSetup::ORIENTATION_LANDSCAPE);
					  $Sheet->getPageSetup()->setPaperSize(PHPExcel_Worksheet_PageSetup::PAPERSIZE_A4); 
					  $margin = 0.5 / 2.54;
					  $Sheet->getPageMargins()->setTop($margin);
					  $Sheet->getPageMargins()->setBottom($margin);
					  $Sheet->getPageMargins()->setLeft($margin);
					  $Sheet->getPageMargins()->setRight($margin); 
		
		
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
			
		$tmp = "stat - ".date("dmY His").".xls";	
		
		$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
        $objWriter->save($base_path.$tmp);
		
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












