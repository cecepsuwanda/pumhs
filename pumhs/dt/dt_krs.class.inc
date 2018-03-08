<?php
require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_krs
{
   var $tb;
   var $numrows;  
   var $kls;
   var $kmps;
   var $TA;
     
   function __construct(){
     $this->tb = new tb_krs;
	 
	 $bln=date('n');
	 $thn=date('Y');
	 
	 if(($bln>=3) and ($bln<=8))
	{
	   $this->TA=($thn-1).'2';
	}else{
	 
			 if(($bln>=9) and ($bln<=12))
			 {
			   $this->TA=$thn.'1';
			 }else{
				if(($bln>=1) and ($bln<=2))
				{
				  $this->TA=($thn-1).'1';
				}	 
			 }
	    }
	 
   }
  
    
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function save_krs($data)
	{
	  $this->tb->insertRecord($data);	
	}
	
	function delete_krs($data)
	{
	  $this->tb->deleteRecord($data);	
	}
	
	function periksa($ta,$prodi,$kdmtk,$ktpmhs)
	{
	  $data = $this->getData("thsmskrs=".$ta." and prodi='".$prodi."' and nokmkkrs=".$kdmtk." and noktphskrs='".$ktpmhs."'");	
      	  
	  return $this->numrows>0;	
	}
	
	function getKRS($where)
    {	  
	  
	  $this->tb->sql_select="kd_mk,nm_mk,sks_tot,kelaskrs,kampus";
	  $this->tb->sql_from="tmst_mtk a INNER JOIN tmst_krs b ON thsmskrs=thn_sms AND NO=nokmkkrs";
	  $this->tb->sql_orderby="kd_mk";	  
	  
	  $data = $this->tb->getData($where); 
	  
	  $this->kls="A";
	  $this->kmps="BALEENDAH";
	  if(!empty($data))
	  {
	    foreach($data as $row)
		{
		  $this->kls=$row['kelaskrs'];
	      $this->kmps=$row['kampus'];
		}
	  
	  }
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function getMHS($where)
    {	  
	  
	  //$this->tb->sql_select="tmst_krs.fak,tmst_prodi.prodi,NIM,nama_mahasiswa,SUM(sks_tot) jml_sks";
	  //$this->tb->sql_from="((tmst_krs INNER JOIN tmst_mahasiswa ON noktphskrs=no_ktp) INNER JOIN tmst_prodi ON tmst_krs.prodi=kd_prodi) INNER JOIN tmst_mtk ON NO=nokmkkrs AND thsmskrs=thn_sms";
	 //$this->tb->sql_groupby="fak,tmst_prodi.prodi,no_ktp,nama_mahasiswa";
	  //$this->tb->sql_orderby="tmst_krs.mhsudate desc";	  
	  
	  $tb = new tb_krs_mhs;
	  
	  if($where=="")
	  {
	  	 $where="thsmskrs = ".$this->TA; 
	  }else {
	  
	    $where=$where." and thsmskrs = ".$this->TA;
	  }
	  
	  
	  $data = $tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
	function getProdi($where)
    {	  
	  
	    
	  $tb = new tb_krs_prodi;
	  
	  if($where=="")
	  {
	  	 $where="thsmskrs = ".$this->TA; 
	  }else {
	  
	    $where=$where." and thsmskrs = ".$this->TA;
	  }
	  
	  $data = $tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
	function getMTK($where)
    {	  
	  
	  //$this->tb->sql_select="tmst_krs.fak,tmst_prodi.prodi,semkrs,kd_mk,nm_mk,shiftkrs,kelaskrs,COUNT(kd_mk) jml_mhs";
	  //$this->tb->sql_from="(tmst_krs INNER JOIN tmst_mtk ON nokmkkrs=NO AND thsmskrs=thn_sms)INNER JOIN tmst_prodi ON tmst_krs.prodi=kd_prodi";
	  //$this->tb->sql_groupby="tmst_krs.fak,tmst_prodi.prodi,semkrs,kd_mk,nm_mk,shiftkrs,kelaskrs";
	  //$this->tb->sql_orderby="tmst_krs.fak,tmst_prodi.prodi,semkrs,kd_mk,nm_mk,shiftkrs,kelaskrs";	  
	  
	  $tb = new tb_krs_mtk;
	  
	  if($where=="")
	  {
	  	 $where="thsmskrs = ".$this->TA; 
	  }else {
	  
	    $where=$where." and thsmskrs = ".$this->TA;
	  }
	  
	  
	  $data = $tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}

	function getkhs($prodi,$noktp)
	{
      $this->tb->sql_select="*";
	  $this->tb->sql_from="(tmst_krs INNER JOIN tmst_mtk ON nokmkkrs=NO and thsmskrs=thn_sms and tmst_krs.prodi=tmst_mtk.prodi)";
	  $this->tb->sql_orderby="thsmskrs,kd_mk";
      $data = $this->tb->getData("flag_krs=1 and noktphskrs='$noktp' and tmst_krs.prodi='$prodi'");
	  return $data;
	}
	
	function getDataStat($where)
    {	  
	  $dt_fak_jn_prodi = new dt_fak_jn_prodi;	  
	  $data_struct =array();
	  
	  $this->tb->sql_select="DISTINCT Kode_program_studi as prodi,tahun_masuk,No_KTP";
	  $this->tb->sql_from="tmst_krs INNER JOIN tmst_mahasiswa ON noktphskrs=no_ktp";
	  //$this->tb->sql_groupby="fak,prodi,tahun_masuk";
	  //$this->tb->sql_orderby="kd_fakultas,tahun_masuk";	  
	  
	  $data = $this->tb->getData($where);  
	  
	  if(!empty($data))
	  {
	    foreach($data as $row)
		{
		  $dt_fak=$dt_fak_jn_prodi->getnmfk($row['prodi']);
		  
		  $data_struct[$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $data_struct[$dt_fak['kd_fak']]['Tahun_Masuk'][$row['tahun_masuk']]= isset($data_struct[$dt_fak['kd_fak']]['Tahun_Masuk'][$row['tahun_masuk']])  ? $data_struct[$dt_fak['kd_fak']]['Tahun_Masuk'][$row['tahun_masuk']]+ 1: 1;

		}
	  }
	  
	 
	  //$this->numrows=$this->tb->numrows;
      	 
	  return $data_struct;		 
	  	  
	}
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 