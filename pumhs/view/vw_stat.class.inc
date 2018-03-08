<?php

class vw_stat
{   var $dt;
    var $dt1;
	function __construct()
	{
	  	$this->dt = new dt_fak_jn_prodi;
        $this->dt1 = new dt_mhs;		
	}
	
	function buattbl($lst,$lbl)
	{
		
		$TA = array();
		$jml_ta=array();
		
		$tmp_date =date("Y");
		$j=0;
		$TA[]='0000';
		$jml_ta['0000']=0;
		for ($i=2008;$i<=$tmp_date;$i++){
		  $TA[]=$i;
		  $jml_ta[$i]=0;
		  $j+=1;
		}
		
		$jml_un=0;
				
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $lbl,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header',array('rowspan'=>'2'));	    
		$tbl->addCell('Fakultas', null, 'header',array('rowspan'=>'2'));	   
		$tbl->addCell('Angkatan', null, 'header',array('colspan'=>$j+1));
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
			    								
				$jml1 = isset($val['Tahun_Masuk'][$ta]) ? $val['Tahun_Masuk'][$ta]:0;
				
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
	    
		return $tbl->display($txt1);
	
	}
	
	
		function summary_stat_mng()
	{   
	    
		
		$data = $this->dt1->getdataStat("");
		
        $mythnsem = new mythnsem;
		$ta = $mythnsem->getthnsem(); 
		$nta = $mythnsem->gettxtthnsem($ta,'Tahun Akademik '); 
		
		$dt_krs = new dt_krs;
		$data1 = $dt_krs->getDataStat("thsmskrs=$ta");
		
		//if(!empty($data))
        //{ $kd_fak=""; 
		//  foreach($data as $row)
		 // {
		    
			  //$kd_fak=$row['kd_fakultas'];            
			  //$jmlkrs[$kd_fak]['nm_fak']=$row['fakultas'];
			  //$jmlkrs[$kd_fak][$row['Tahun_masuk']]=$row['jml'];
              						
		 // }
		//}
		
				
		$txt="<center><H1>REKAPITULASI<BR> PENDATAAN ULANG MAHASISWA (PUMHS)<br>ONLINE</H1><br>Kondisi Data Pada Tanggal :".date("Y-m-d H:i:s")."</center><br>";
		
		$txt=$txt."<fieldset><legend>Data Masuk :</legend><div>";
		$txt=$txt.$this->buattbl($data['jmlttl'],"lst_stat_uns");					 
		$txt=$txt."</div></fieldset><br>";		
		
		$txt=$txt."<fieldset><legend>Data Belum Layak Verifikasi :</legend><div>";
		$txt=$txt.$this->buattbl($data['jmlblmlyk'],"lst_stat_uns1");					 
		$txt=$txt."</div></fieldset><br>";	
				
		$txt=$txt."<fieldset><legend>Data Layak Verifikasi :</legend><div>";
		$txt=$txt.$this->buattbl($data['jmlval'],"lst_stat_uns2");					 
		$txt=$txt."</div></fieldset><br>";
		
		$txt=$txt."<fieldset><legend>Data Sedang Diverifikasi :</legend><div>";
		$txt=$txt.$this->buattbl($data['jmlsdver'],"lst_stat_uns3");					 
		$txt=$txt."</div></fieldset><br>";
				
		$txt=$txt."<fieldset><legend>Data Lolos Verifikasi :</legend><div>";
		$txt=$txt.$this->buattbl($data['jmlver'],"lst_stat_uns4");					 
		$txt=$txt."</div></fieldset><br>";		
		
		$txt=$txt."<fieldset><legend>Data KRS $nta :</legend><div>";
		$txt=$txt.$this->buattbl($data1,"lst_stat_uns5");					 
		$txt=$txt."</div></fieldset><br>";
		
		$txt=$txt."Keterangan : <br>";
        
		$txt2 = "<ul>";
		//$txt2 = $txt2."<li> Data belum di verifikasi Prodi dan Fakultas </li>";
		$txt2 = $txt2."<li> Data belum di klasifikasi Pusat dan KBB </li>";
		$txt2 = $txt2."</ul>";
		
		return $txt.$txt2;
	    //return $jmlfak['FAPERTA'][2013];
	}
	
}
?>












