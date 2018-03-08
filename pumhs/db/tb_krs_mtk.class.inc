<?php
require_once 'default_table.class.inc';
class tb_krs_mtk extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'krs_mtk';
        
		$this->fieldlist       = array('thsmskrs','fak','kd_prodi','prodi','semkrs','kd_mk','nm_mk','shiftkrs','kelaskrs','jml_mhs');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['thsmskrs'] = array('pkey' => 'y');
		$this->fieldlist['fak'] = array('pkey' => 'y');
		$this->fieldlist['prodi'] = array('pkey' => 'y');
		$this->fieldlist['NIM'] = array('pkey' => 'y');
		$this->fieldlist['nama_mahasiswa'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>
