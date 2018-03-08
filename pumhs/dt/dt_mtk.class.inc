<?php
 require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_mtk
{
   var $tb;
   var $numrows;  
   var $kd_lab;
   var $mtk_no;
     
   function __construct(){
     $this->tb = new tb_mtk;
	 
   }
  
    
	function getData($where)
    {	  
	  $this->tb->sql_orderby='sem';
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function carisem($ta,$fak,$kd_prodi,$no)
	{
	  $data = $this->getData("thn_sms=".$ta." and fak='".$fak."' and prodi='".$kd_prodi."' and no=".$no);
	  $sem=0;	  
	  if(!empty($data)){
	    foreach($data as $row){
		  $sem=$row['sem'];
		  $this->kd_lab=$row['kd_lab'];
		  $this->mtk_no=$this->carino($ta,$fak,$kd_prodi,$row['kd_lab']);
		}
	  
	  }
	  
	   return $sem;
	}
	
	function carino($ta,$fak,$kd_prodi,$kdkmk)
	{
	
	  $data = $this->getData("thn_sms=".$ta." and fak='".$fak."' and prodi='".$kd_prodi."' and kd_mk='".$kdkmk."'");
	  $no=0;	  
	  if(!empty($data)){
	    foreach($data as $row){
		  $no=$row['NO'];		  
		}
	  
	  }
	  
	   return $no;
	
	}
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 