<?php
 require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_krs
{
   var $tb;
   var $numrows;  
   var $kls;
   var $kmps;
     
   function __construct(){
     $this->tb = new tb_krs;
	 
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
	  
	  $this->tb->sql_select="kd_mk,nm_mk,sks_tot,kelaskrs,kampus,nilaikrs,bobotkrs";
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
	  
	  $this->tb->sql_select="tmst_krs.fak,tmst_prodi.prodi,NIM,nama_mahasiswa,Kelas,Status_awal_mahasiswa,SUM(sks_tot) jml_sks";
	  $this->tb->sql_from="((tmst_krs INNER JOIN tmst_mahasiswa ON noktphskrs=no_ktp) INNER JOIN tmst_prodi ON tmst_krs.prodi=kd_prodi) INNER JOIN tmst_mtk ON NO=nokmkkrs AND thsmskrs=thn_sms";
	  $this->tb->sql_groupby="fak,tmst_prodi.prodi,no_ktp,nama_mahasiswa,Kelas,Status_awal_mahasiswa";
	  $this->tb->sql_orderby="NIM,nama_mahasiswa";	  
	  
	  $data = $this->tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function getMHS1($where)
    {	  
	  
	  $this->tb->sql_select="*";
	  $this->tb->sql_from="tmst_krs INNER JOIN tmst_mahasiswa ON noktphskrs=no_ktp";
	  $this->tb->sql_groupby="";
	  $this->tb->sql_orderby="NIM,nama_mahasiswa";	  
	  
	  $data = $this->tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function getMTK($where)
    {	  
	  
	  $this->tb->sql_select="tmst_krs.fak,tmst_prodi.prodi,semkrs,nokmkkrs,kd_mk,nm_mk,shiftkrs,kelaskrs,kampus,COUNT(kd_mk) jml_mhs,sum(if(nilaikrs='T',1,0)) as jmlT";
	  $this->tb->sql_from="(tmst_krs INNER JOIN tmst_mtk ON nokmkkrs=NO AND thsmskrs=thn_sms)INNER JOIN tmst_prodi ON tmst_krs.prodi=kd_prodi";
	  $this->tb->sql_groupby="tmst_krs.fak,tmst_prodi.prodi,semkrs,nokmkkrs,kd_mk,nm_mk,shiftkrs,kelaskrs,kampus";
	  $this->tb->sql_orderby="tmst_krs.semkrs,kelaskrs,tmst_krs.shiftkrs,kd_mk";	  
	  
	  $data = $this->tb->getData($where);  
	  
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}

	function update_krs($data)
	{
	  $this->tb->updateRecord($data);	
	}
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 