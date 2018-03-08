<?php

class vw_operator
{  
    var $dt_operator;
	function __construct()
	{
	  	
        $this->dt_operator = new dt_operator;		
	}	
	function vw_change_pass()
	{
	  $frm = new HTML_Form();
      $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_opt"));
	  
	  $tbl->addRow();
	  $tbl->addCell('Password Lama', null, 'data');
	  $tbl->addCell($frm->addInput('password',"lama","",array('id'=>'lama','maxlength'=>"10")), null, 'data');	
	  $tbl->addRow();
	  $tbl->addCell('Password Baru', null, 'data');
	  $tbl->addCell($frm->addInput('password',"baru","",array('id'=>'baru','maxlength'=>"10")), null, 'data');
      $tbl->addRow();
	  $tbl->addCell('Konfirmasi Password Baru', null, 'data');
	  $tbl->addCell($frm->addInput('password',"konf_baru","",array('id'=>'konf_baru','maxlength'=>"10")), null, 'data');	  
	  $tbl->addRow();
	  $tbl->addCell($frm->addInput('button',"save","save",array('onclick'=>'cekform1()')), null, 'data',array("align" => "center","valign"=>"middle","colspan"=>"2"));
				
	
	  return "<br><div id='loginContainer'><h1>Ganti Password</h1>".$frm->startForm(null,'post','gnt-pass').$tbl->display().$frm->endForm()."</div>";
	}
	
}
?>












