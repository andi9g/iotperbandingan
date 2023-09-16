<div>
    <div wire:poll.keep-alive>
        <div class="row">
            <div class="col-12 col-sm-6 col-md-6">
                <div class="info-box">
                    <span class="info-box-icon bg-info elevation-1">
                        <i class="fas fa-thermometer-half "></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">SUHU</span>
                        <span class="info-box-number">
                            <h5>
                                <b>
                                    {{ $suhu }}
                                </b>
                            </h5>
                        </span>
                    </div>

                </div>

            </div>

            

            <div class="clearfix hidden-md-up"></div>
            <div class="col-12 col-sm-6 col-md-6">
                <div class="info-box mb-3">
                    <span class="info-box-icon bg-danger elevation-1">
                        <i class="fas fa-bolt"></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">TEGANGAN</span>
                        <span class="info-box-number">
                            <h5>
                                <b>
                                    {{ $tegangan }}
                                </b>
                            </h5>
                        </span>
                    </div>

                </div>

            </div>

            
            <div class="col-12 col-sm-12 col-md-12">
                <div class="info-box mb-3">
                    <span class="info-box-icon bg-success elevation-1">
                        <i class="fas fa-calendar"></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">TANGGAL & JAM</span>
                        <span class="info-box-number">
                            <h5>
                                <b>
                                    {{ $tanggal }}
                                </b>
                            </h5>
                        </span>
                    </div>

                </div>

            </div>

        </div>
    </div>
</div>
