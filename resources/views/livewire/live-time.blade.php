<div>
    <div wire:poll.keep-alive>
        <div class="row">
            <div class="col-12 col-sm-6 col-md-4">
                <div class="info-box">
                    <span class="info-box-icon bg-info elevation-1">
                        <i class="fas fa-thermometer-half "></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">SUHU</span>
                        <span class="info-box-number">
                            <h3>
                                <b>
                                    {{ $suhu }}
                                </b>
                            </h3>
                        </span>
                    </div>

                </div>

            </div>

            <div class="col-12 col-sm-6 col-md-4">
                <div class="info-box mb-3">
                    <span class="info-box-icon bg-primary elevation-1">
                        <i class="fas fa-thermometer "></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">KELEMBABAN</span>
                        <span class="info-box-number">
                            <h3>
                                <b>
                                    {{ $kelembaban }}
                                </b>
                            </h3>
                        </span>
                    </div>

                </div>

            </div>

            <div class="clearfix hidden-md-up"></div>
            <div class="col-12 col-sm-6 col-md-4">
                <div class="info-box mb-3">
                    <span class="info-box-icon bg-danger elevation-1">
                        <i class="fas fa-bolt"></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">TEGANGAN</span>
                        <span class="info-box-number">
                            <h3>
                                <b>
                                    {{ $tegangan }}
                                </b>
                            </h3>
                        </span>
                    </div>

                </div>

            </div>

            
            <div class="col-12 col-sm-8 col-md-8">
                <div class="info-box mb-3">
                    <span class="info-box-icon bg-success elevation-1">
                        <i class="fas fa-calendar"></i>
                    </span>
                    <div class="info-box-content">
                        <span class="info-box-text text-lg">TANGGAL & JAM</span>
                        <span class="info-box-number">
                            <h3>
                                <b>
                                    {{ $tanggal }}
                                </b>
                            </h3>
                        </span>
                    </div>

                </div>

            </div>

        </div>
    </div>
</div>
